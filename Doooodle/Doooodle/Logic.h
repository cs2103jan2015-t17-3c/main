
#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <ctime>
#include <chrono>
#include "Parser.h"
#include "Storage.h"
#include "CommandDetails.h"

using namespace std;

class Logic {

public:
	Logic(void);
	~Logic(void);
	string receiveCommand(string);

private:

//	Storage storage;
//	Parser parser;
	CommandDetails commandDetails;

	enum COMMAND_TYPE {
		ADD, DELETE, EDIT, SEARCH, HELP, ARCHIVE 
	};

	string executeLogicCore(string);
	COMMAND_TYPE getCommandType(string);

};


#endif