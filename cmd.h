#pragma once
#include <vector>
#include <string>
#include <ctime>

class Observer;

enum ERROR_CODES {
	ERROR_NOT_ONE_COMMAND_IN_LINE,
	SUCCESS
};

class cmdBulk
{
public:
	cmdBulk();
	cmdBulk(size_t bulkStandartSize);

	void addCMD(std::string cmd);
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
	void notify();
private:
	std::vector<std::string> cmdPack;
	std::vector<Observer*> subs;

	unsigned int bulkTimeStart;
	size_t bulkSize;
	int startBulkCounter;

private:
	size_t commandParsing(std::string& cmd, std::string& dynBulk);
};