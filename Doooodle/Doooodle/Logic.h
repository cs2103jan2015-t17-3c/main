
#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <vector>
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "CommandDetails.h"
#include "NormalTask.h"
#include "DeadlineTask.h"
#include "FloatingTask.h"

using namespace std;

class Logic {

public:
	Logic(void);
	~Logic(void);
	string receiveCommand(string);
	vector<string> displayTopFive(void);

private:
	Storage storage;
	Parser parser;
	NormalTask normTask;
	DeadlineTask deadlineTask;
	FloatingTask floatingTask;
	vector<CommandDetails*> commandDetails;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE 
	};

	string executeLogicCore(string);
	TASK_TYPE determineSpecificTaskType(int);
};


#endif