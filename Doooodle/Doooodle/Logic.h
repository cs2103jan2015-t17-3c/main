
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
#include "RedoTask.h"
#include "DeleteSearchTask.h"

using namespace std;

class Logic {

public:
	Logic(void);
	~Logic(void);
	string receiveCommand(string);
	vector<string> displayTopTen(void);
	vector<string> displaySearchResults(string);
	bool isSearch(string);

private:
	Storage storage;
	Parser parser;
	NormalTask normTask;
	DeadlineTask deadlineTask;
	FloatingTask floatingTask;
	UndoTask undoTask;
	RedoTask redoTask;
	DeleteTask deleteTask;
	DeleteSearchTask deleteSearchTask;
	SearchTask searchTask;
	EditTask editTask;
	static const string STRING_ADD;
	static const string STRING_DELETE;
	static const string STRING_EDIT;
	static const string STRING_EXIT;
	static const string STRING_INVALID;
	static const string STRING_REDO;
	static const string STRING_SEARCH;
	static const string STRING_UNDO;

	vector<CommandDetails*> commandDetails;
	vector<CommandDetails*> commandDetailsForRedo;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE, SEARCH, EXIT, INVALID, UNDO, EDIT, REDO
	};

	string executeLogicCore(string);
	string executeTask(TASK_TYPE, int);
	TASK_TYPE determineSpecificTaskType(int);
	bool lastCommandIsSearch(void);
};


#endif