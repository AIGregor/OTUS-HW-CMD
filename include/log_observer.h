#pragma once
#include "cmd.h"

class Observer 
{
public:
	virtual void update(cmdBulk* bulk, size_t errorCode) = 0;
};

class log_observer : public Observer
{
public:
	log_observer(cmdBulk* bulk) {
		bulk->sibscribe(this);
	};

	void update(cmdBulk* bulk, size_t errorCode);
private:
	void saveLog(std::string fileName, std::vector<std::string>& bulk);
	void saveLog(std::string fileName, size_t errorCode);
};

class consol_observer : public Observer
{
public:
	consol_observer(cmdBulk* bulk) {
		bulk->sibscribe(this);
	};

	void update(cmdBulk* bulk, size_t errorCode);
private:
	void printToConsol(const std::vector<std::string>& bulk);
	void printToConsol(size_t errorCode);
};