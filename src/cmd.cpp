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

void cmdBulk::add(std::string cmd)
{
	// split input line and add to bulk
	size_t result = parse(cmd);
	
	if (result != ERROR_CODES::SUCCESS)
	{
		notify(result);
	}
}

void cmdBulk::addCMD(std::string cmd)
{
	if (cmd.empty())
		return;

	if (cmd.compare("{") == 0)
	{	
		++startBulkCounter;
		if (startBulkCounter == 1) {
			cmdPack.clear();
		}
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

size_t cmdBulk::parse(std::string& cmd)
{	
	// Split by space	
	std::istringstream iss(cmd);
	std::vector<std::string> line_parts{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	//std::stringstream ss(cmd);
	//std::istream_iterator<std::string> begin(ss);
	//std::istream_iterator<std::string> end;
	//
	//std::vector<std::string> line_parts(begin, end);
	//std::copy(line_parts.begin(), line_parts.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	// Only one command in line for case { cmd1 }
	// In other case looking each part
	if (line_parts.size() > 3) {
		return ERROR_CODES::ERROR_NOT_ONE_COMMAND_IN_LINE;
	}

	size_t cmdCounter = 0;
	for (auto& str : line_parts)
	{
		// Case - {cmd1} or cmd1{}cmd2 or cmd1{cmd2} 
		// Case - {}cmd or cmd{} or {cmd1}cmd2
		// Case - }cmd{ or cmd1}{ or }{cmd1
		// Case - cmd{ or {cmd or cmd1{cmd2

		bool startBulk = false;
		bool endBulk = false;

		if (str.compare("{") == 0 ||
			str.compare("}") == 0)
		{
			addCMD(str);
			continue;
		}

		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '{')
			{
				str.replace(i, 1, " { ");
				startBulk = true;
				++i;
			}
			else if (str[i] == '}')
			{
				str.replace(i, 1, " } ");
				endBulk = true;
				++i;
			}
		}

		// In one line { or } and command 
		if (endBulk || startBulk)
		{
			// split again
			size_t res = parse(str);
			if (res != ERROR_CODES::SUCCESS)
				return res;
		}
		else
		{
			addCMD(str);
		}
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
}