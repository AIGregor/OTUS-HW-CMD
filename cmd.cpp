#include "cmd.h"
#include "log_observer.h"

cmdBulk::cmdBulk() :
	bulkSize(0),
	startBulkCounter(0)
{
}

cmdBulk::cmdBulk(size_t bulkStandartSize) :
	bulkSize(bulkStandartSize),
	startBulkCounter(0)
{
}

void cmdBulk::addCMD(std::string cmd)
{
	if (cmd.empty())
		return;

	if (cmd.find("{") != std::string::npos)
	{	
		++startBulkCounter;		
		return;
	}
	else if (cmd.find("}") != std::string::npos)
	{
		if (startBulkCounter > 0)
		{
			--startBulkCounter;
			if (startBulkCounter == 0)
			{
				notify();
				cmdPack.clear();
			}
		}		
		return;
	}

	if (cmdPack.size() == 0)
		bulkTimeStart = time(NULL);

	cmdPack.push_back(cmd);

	if (startBulkCounter == 0 && cmdPack.size() == bulkSize)
	{
		notify();
		cmdPack.clear();
	}
}

void cmdBulk::sibscribe(Observer * obs)
{
	subs.push_back(obs);
}

void cmdBulk::notify()
{
	for (auto s : subs) {
		s->update(this);
	}
}