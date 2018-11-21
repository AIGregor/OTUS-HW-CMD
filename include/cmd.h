#pragma once
#include <vector>
#include <string>
#include <ctime>

class Observer;

enum CODES {	
	ERROR_ARGUMENT_LIST,
	ERROR_NOT_ONE_COMMAND_IN_LINE,
	ERROR_THERE_IS_NO_OPENING_BRACKET,
	SUCCESS,
	COMMAND,
	START_BRACKET,
	END_BRACKET
};

static const std::string ERROR_MESSAGES[3] = 
{
	"There is no arguments list.",
	"ERROR. Only one command in line.",
	"ERROR. There is no any opening brackets."
};

class cmdBulk
{
public:
	cmdBulk();
	cmdBulk(size_t bulkStandartSize);

	void add(std::string& cmd);

	std::vector<std::string>& getBulk() { 
		return cmdPack; 
	};
	auto getTimeStart() { 
		return std::to_string(bulkTimeStart); 
	};
	bool isDynamicSizeBulk() {
		return startBulkCounter > 0; 
	};

	size_t checkDynamicSizeBulk(const std::string& bracket);

	void sibscribe(Observer* obs);
	void notify(size_t errorCode = CODES::SUCCESS);

private:
	std::vector<std::string> cmdPack;
	std::vector<Observer*> subs;

	unsigned int bulkTimeStart;
	size_t bulkSize;
	int startBulkCounter;
	bool hasCommand;
private:
	size_t addCMD(const std::string& cmd);
	size_t parse(std::string& cmd);
};