#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
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
	
	if (result != CODES::SUCCESS)
	{
		notify(result);
	}
}

size_t cmdBulk::addCMD(const std::string& cmd)
{
	if (cmd.empty())
		return CODES::SUCCESS;

	if (cmdPack.size() == 0)
		bulkTimeStart = time(NULL);

	cmdPack.push_back(cmd);

	if (startBulkCounter == 0 && cmdPack.size() == bulkSize)
	{
		notify();
	}

	return CODES::SUCCESS;
}

size_t cmdBulk::parse(std::string& cmd)
{	
	// Split command line
	std::istringstream iss(cmd);
	std::vector<std::string> line_parts{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	// Only one command in line for case { cmd1 }
	// In other case looking each part
	std::vector<std::string> cmd_parts;

	int iLocalBulkCounter, iCmdCounter;
	iLocalBulkCounter = iCmdCounter = 0;

	for (auto& cmd : line_parts)
	{
		// Check brackets
		size_t res = checkDynamicSizeBulk(cmd);

		switch (res)
		{
		case CODES::START_BRACKET:
			++iLocalBulkCounter;
			continue;
		case CODES::END_BRACKET:
			--iLocalBulkCounter;
			continue;
		case CODES::COMMAND:			
			if (iCmdCounter > 0)
			{
				startBulkCounter -= iLocalBulkCounter;
				cmdPack.clear();
				return CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
			}
			addCMD(cmd);
			++iCmdCounter;
			continue;
		}
	
		return res;
	}

	return CODES::SUCCESS;
}

size_t cmdBulk::checkDynamicSizeBulk(const std::string & bracket)
{
	if (bracket.compare("{") == 0)
	{
		++startBulkCounter;
		if (startBulkCounter == 1) {
			notify();
		}
		return CODES::START_BRACKET;
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
			return CODES::ERROR_THERE_IS_NO_OPENING_BRACKET;
		}
		return CODES::END_BRACKET;
	}

	return CODES::COMMAND;
}

void cmdBulk::sibscribe(Observer * obs)
{
	subs.push_back(obs);
}

void cmdBulk::notify(size_t errorCode /*= CODES::SUCCESS*/)
{
	for (const auto& s : subs) {
		s->update(*this, errorCode);
	}
	cmdPack.clear();
}