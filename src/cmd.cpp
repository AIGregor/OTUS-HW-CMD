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

void cmdBulk::add(std::string& cmd)
{
	// split input line and add to bulk
	size_t result = parse(cmd);
	
	if (result != ERROR_CODES::SUCCESS)
	{
		notify(result);
	}
}

size_t cmdBulk::addCMD(std::string& cmd)
{
	if (cmd.empty())
		return ERROR_CODES::SUCCESS;

	if (cmd.compare("{") == 0)
	{	
		++startBulkCounter;
		if (startBulkCounter == 1) {
			notify();
		}
		return ERROR_CODES::SUCCESS;
	}
	else if (cmd.compare("}") == 0)
	{
		if (startBulkCounter > 0)
		{
			--startBulkCounter;
			if (startBulkCounter == 0)
			{
				notify();
			}
		}
		else
		{
			return ERROR_CODES::ERROR_THERE_IS_NO_OPENING_BRACKET;
		}
		return ERROR_CODES::SUCCESS;
	}

	if (cmdPack.size() == 0)
		bulkTimeStart = time(NULL);

	cmdPack.push_back(cmd);

	if (startBulkCounter == 0 && cmdPack.size() == bulkSize)
	{
		notify();
	}

	return ERROR_CODES::SUCCESS;
}

size_t cmdBulk::parse(std::string& cmd)
{	
	// Split by space	
	std::istringstream iss(cmd);
	std::vector<std::string> line_parts{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	size_t cmdCounter = 0;
	for (auto& str : line_parts)
	{
		if (str != "{" && str != "}")
		{
			++cmdCounter;
		}

		// Only one command in line for case { cmd1 }
		// In other case looking each part
		if (cmdCounter > 1) {
			return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
		}
	}

	for (auto& str : line_parts)
	{
		// There are all commands :
		// {cmd1} or cmd1{}cmd2 or cmd1{cmd2} 
		// {}cmd or cmd{} or {cmd1}cmd2
		// }cmd{ or cmd1}{ or }{cmd1
		// cmd{ or {cmd or cmd1{cmd2
		
		size_t errorCode = addCMD(str);
		if (errorCode != ERROR_CODES::SUCCESS)
			return errorCode;
	}

	return ERROR_CODES::SUCCESS;
}

void cmdBulk::sibscribe(Observer * obs)
{
	subs.push_back(obs);
}

void cmdBulk::notify(size_t errorCode /*= ERROR_CODES::SUCCESS*/)
{
	for (auto s : subs) {
		s->update(this, errorCode);
	}
	cmdPack.clear();
}