#include "log_observer.h"
#include <iostream>
#include <fstream>

void log_observer::saveLog(std::string fileName, std::vector<std::string>& bulk)
{	
	int size = bulk.size();	
	if (size <= 0)
		return;

	std::ofstream out;

	out.open(fileName);
	if (out.is_open())
	{
		int size = bulk.size();
		out << "bulk: ";
		for (int i = 0; i < size; ++i)
		{
			out << bulk[i];
			i < size - 1 ? out << ", " :
				out << std::endl;
		}
	}
}

void log_observer::saveLog(std::string fileName, size_t errorCode)
{
	std::ofstream out;

	out.open(fileName);
	if (out.is_open())
	{
		out << ERROR_MESSAGES[errorCode] << std::endl;
	}
}

void log_observer::update(cmdBulk* bulk, size_t errorCode)
{
	std::string fileName = "bulk" + bulk->getTimeStart() + ".log";
	if (errorCode == ERROR_CODES::SUCCESS)
	{
		saveLog(fileName, bulk->getBulk());
	}
	else
	{
		saveLog(fileName, errorCode);
	}
	
}

void consol_observer::update(cmdBulk* bulk, size_t errorCode)
{
	if (errorCode == ERROR_CODES::SUCCESS)
	{
		printToConsol(bulk->getBulk());
	}	
	else
	{
		printToConsol(errorCode);
	}
}

void consol_observer::printToConsol(const std::vector<std::string>& bulk)
{
	// TODO вывести в консоль
	int size = bulk.size();
	if (size <= 0)
		return;

	std::cout << "bulk: ";
	for (int i = 0; i < size; ++i)
	{		
		std::cout << bulk[i];
		i < (size - 1) ? std::cout << ", " : 
						std::cout << std::endl;
	}
}

void consol_observer::printToConsol(size_t errorCode)
{
	std::cout << ERROR_MESSAGES[errorCode] << std::endl;
}
