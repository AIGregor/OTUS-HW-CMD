#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
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

	std::string bulk;
	size_t res = commandParsing(cmd, bulk);

	if (cmd.compare("{") == 0)
	{	
		++startBulkCounter;		
		return;
	}
	else if (cmd.compare("}") == 0)
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

size_t cmdBulk::commandParsing(std::string& cmd, std::string& dynBulk)
{	
	std::stringstream ss(cmd);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;

	std::vector<std::string> line_parts(begin, end);
	std::copy(line_parts.begin(), line_parts.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	if (line_parts.size() > 3) {
		return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
	}

	size_t cmdCounter = 0;
	for (auto& str : line_parts) {
		// Case - {cmd1 cmd2}
		if (cmdCounter > 1) {
			return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
		}
		
		// Case - comand1 {cmd1}
		size_t startBulk_pos;
		size_t endBulk_pos;

		startBulk_pos = str.find("{");
		endBulk_pos = str.find("}");

		// Case {cmd}
		if (startBulk_pos != std::string::npos &&
			endBulk_pos != std::string::npos) 
		{
			cmdCounter = 1;
			str.erase(startBulk_pos, 1);
			str.erase(endBulk_pos, 1);
			cmd = str;
		}
		
		// Get start bulk if it was find
		if (startBulk_pos != std::string::npos) {
			dynBulk = cmd.substr(startBulk_pos);
			cmd.erase(startBulk_pos);
		}

		// Get end bulk if it was find
		if (endBulk_pos != std::string::npos) {
			dynBulk = cmd.substr(endBulk_pos);
			cmd.erase(endBulk_pos);
		}

		// Case command{command or command}command
		if (dynBulk.size() > 1) {
			return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
		}
	}
	
	// Delete all space symbols
	//dynBulk.erase(std::remove_if(dynBulk.begin(), dynBulk.end(), isspace), dynBulk.end());
	
	return ERROR_CODES::SUCCESS;
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