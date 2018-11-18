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
	startBulkCounter(0),
	hasCommand(false)
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

size_t cmdBulk::addCMD(const std::string& cmd)
{
	if (cmd.empty())
		return ERROR_CODES::SUCCESS;

	// Check brackets
	size_t res = checkDynamicSizeBulk(cmd);
	if (res != ERROR_CODES::COMMAND)
		return res;

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
	// Flag - has command on this line
	hasCommand = false;

	// Split command line
	std::istringstream iss(cmd);
	std::vector<std::string> line_parts{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	for (size_t i = 0; i < line_parts.size(); ++i)
	{		
		size_t errorCode = addCMD(line_parts[i]);
		if (errorCode != ERROR_CODES::SUCCESS)
			return errorCode;
	}

	return ERROR_CODES::SUCCESS;
}

size_t cmdBulk::checkDynamicSizeBulk(const std::string & bracket)
{
	if (bracket.compare("{") == 0)
	{
		++startBulkCounter;
		if (startBulkCounter == 1) {
			notify();
		}
		return ERROR_CODES::SUCCESS;
	}
	if (bracket.compare("}") == 0)
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

	// Only one command in line for case { cmd1 }
	// In other case looking each part
	if (hasCommand) {
		return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
	}
	hasCommand = true;

	return ERROR_CODES::COMMAND;
}

void cmdBulk::sibscribe(Observer * obs)
{
	subs.push_back(obs);
}

void cmdBulk::notify(size_t errorCode /*= ERROR_CODES::SUCCESS*/)
{
	for (const auto& s : subs) {
		s->update(*this, errorCode);
	}
	cmdPack.clear();
}