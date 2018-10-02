#pragma once
#include <vector>
#include <string>
#include <ctime>

class Observer;

enum ERROR_CODES {	
	ERROR_ARGUMENT_LIST,
	ERROR_NOT_ONE_COMMAND_IN_LINE,
	SUCCESS
};

static const std::string ERROR_MESSAGES[2] = 
{
	"There is no arguments list.",
	"ERROR. Only one command in line."
};

class cmdBulk
{
public:
	cmdBulk();
	cmdBulk(size_t bulkStandartSize);

	void add(std::string cmd);

	std::vector<std::string>& getBulk() { 
		return cmdPack; 
	};
	auto getTimeStart() { 
		return std::to_string(bulkTimeStart); 
	};
	bool isDynamicSizeBulk() {
		return startBulkCounter > 0; 
	};

	void sibscribe(Observer* obs);
	void notify(size_t errorCode = ERROR_CODES::SUCCESS);

private:
	std::vector<std::string> cmdPack;
	std::vector<Observer*> subs;

	unsigned int bulkTimeStart;
	size_t bulkSize;
	int startBulkCounter;

private:
	void addCMD(std::string cmd);
	size_t parse(std::string& cmd);
};