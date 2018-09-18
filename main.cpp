#include <iostream>
#include <string>

#include "log_observer.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Argument is necessary
	if (argc < 2)
		return 0;

	// Standart bulk size
	long bulkSize = atol(argv[1]);

	cmdBulk cmdBulk(bulkSize);
	log_observer log(&cmdBulk);
	consol_observer consl(&cmdBulk);

	while (cin)
	{
		std::string cmd;
		getline(cin, cmd);

		cmdBulk.addCMD(cmd);
	}

	if (!cmdBulk.isDynamicSizeBulk())
		cmdBulk.notify();

	return 0;
}