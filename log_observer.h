#pragma once
#include "cmd.h"

class Observer 
{
public:
	virtual void update(cmdBulk* bulk) = 0;
};

class log_observer : public Observer
{
public:
	log_observer(cmdBulk* bulk) {
		bulk->sibscribe(this);
	};

	void update(cmdBulk* bulk);
private:
	void saveLog(std::string fileName, std::vector<std::string>& bulk);
};

class consol_observer : public Observer
{
public:
	consol_observer(cmdBulk* bulk) {
		bulk->sibscribe(this);
	};

	void update(cmdBulk* bulk);
private:
	void printToConsol(const std::vector<std::string>& bulk);

};

