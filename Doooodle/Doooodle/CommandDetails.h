
#ifndef COMMANDDETAILS_H_
#define COMMANDDETAILS_H_

#include <iostream>

using namespace std;

class CommandDetails {

public:
	string commandType;
	string task;
	string timeStart;
	string timeEnd;
	string itemToDelete;

	CommandDetails(void);
	~CommandDetails(void);
};

#endif