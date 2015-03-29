
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
#include "RescheduleTask.h"
#include "OverdueTask.h"

using namespace std;

class Logic {

public:
	Logic(void);
	~Logic(void);
	string receiveCommand(string);
	vector<string> displayTopTen(void);
	vector<string> displayFloatingTask(void);
	vector<string> displaySearchResults(string);
	vector<string> displayOverdue(void);
	vector<string> displayCategoricalTask(string, string&);
	string getCommandType(string);

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
	RescheduleTask rescheduleTask;
	OverdueTask overdueTask;
	static const string STRING_ADD;
	static const string STRING_ARCHIVE;
	static const string STRING_CHECK;
	static const string STRING_COMPLETE;
	static const string STRING_COMPLETED;
	static const string STRING_DISPLAY;
	static const string STRING_DEADLINE;
	static const string STRING_DELETE;
	static const string STRING_EDIT;
	static const string STRING_EXIT;
	static const string STRING_FLOATING;
	static const string STRING_INVALID;
	static const string STRING_NORMAL;
	static const string STRING_RESCHEDULE;
	static const string STRING_SEARCH;
	static const string STRING_UNDO;
	static const int TOP10MAX;
	static const int FLOATMAX;

	vector<CommandDetails*> commandDetails;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE, SEARCH, EXIT, INVALID, UNDO, EDIT, ARCHIVE, CHECK, RESCHEDULE, COMPLETE, COMPLETED
	};

	string executeLogicCore(string);
	string executeTask(TASK_TYPE, int);
	TASK_TYPE determineSpecificTaskType(int);
	bool lastCommandIsSearch(void);
};


#endif