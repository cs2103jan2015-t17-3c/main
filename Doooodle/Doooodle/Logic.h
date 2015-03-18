
#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
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
	vector<string> displaySearchResult(string);
	bool isSearch(string);

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
	static char buffer[300];
	static const string MESSAGE_ADD;
	static const string MESSAGE_DELETE;
	static const string MESSAGE_EDIT;
	static const string MESSAGE_EXIT;
	static const string MESSAGE_INVALID;
	static const string MESSAGE_REDO;
	static const string MESSAGE_SEARCH;
	static const string MESSAGE_UNDO;

	vector<CommandDetails*> commandDetails;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE, SEARCH, EXIT, INVALID, UNDO, EDIT
	};

	vector<string> executeLogicCore(string);
	vector<string> executeTask(TASK_TYPE, int);
	TASK_TYPE determineSpecificTaskType(int);
};


#endif