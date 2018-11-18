#include <iostream>
#include <string>

#include "log_observer.h"

int main(int argc, char *argv[])
{
	using namespace std;

	// Argument is necessary
	if (argc < 2)
	{
		cout << ERROR_MESSAGES[ERROR_CODES::ERROR_ARGUMENT_LIST];
		return 0;
	}		

	// Standart bulk size
	long bulkSize = atol(argv[1]);

	cmdBulk cmdBulk(bulkSize);
	log_observer log(cmdBulk);
	consol_observer consl(cmdBulk);

	while (cin)
	{
		std::string cmd;
		getline(cin, cmd);

		cmdBulk.add(cmd);
	}

	if (!cmdBulk.isDynamicSizeBulk())
		cmdBulk.notify();

	return 0;
}