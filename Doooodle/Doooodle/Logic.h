
#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <vector>
#include <string>
#include <boost/date_time.hpp>
#include "Parser.h"
#include "Storage.h"
#include "CommandDetails.h"
#include "NormalTask.h"
#include "DeadlineTask.h"
#include "FloatingTask.h"
#include "UndoTask.h"
#include "DeleteTask.h"
#include "SearchTask.h"
#include "EditTask.h"

using namespace std;

class Logic {

public:
	Logic(void);
	~Logic(void);
	vector<string> receiveCommand(string);
	vector<string> displayTopFive(void);

private:
	Storage storage;
	Parser parser;
	NormalTask normTask;
	DeadlineTask deadlineTask;
	FloatingTask floatingTask;
	UndoTask undoTask;
	DeleteTask deleteTask;
	SearchTask searchTask;
	EditTask editTask;

	vector<CommandDetails*> commandDetails;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE, SEARCH, EXIT, INVALID, UNDO, EDIT
	};

	vector<string> executeLogicCore(string);
	vector<string> executeTask(TASK_TYPE, int);
	TASK_TYPE determineSpecificTaskType(int);
};


#endif