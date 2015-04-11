
#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "Parser.h"
#include "Storage.h"
#include "CommandDetails.h"
#include "NormalTask.h"
#include "DeadlineTask.h"
#include "FloatingTask.h"
#include "OverdueTask.h"
#include "UndoTask.h"
#include "DeleteTask.h"
#include "SearchTask.h"
#include "EditTask.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class Logic {

public:
	Logic(void);
	~Logic(void);
	//facade function for GUI to call logic to process user commands
	std::string receiveCommand(std::string);

	//getter functions for GUI
	std::vector<std::string> displayTopList(void);
	std::vector<std::string> displayFloatingTask(void);
	std::vector<std::string> displaySearchResults(std::string);
	std::vector<std::string> displayCategoricalTask(std::string, std::string&);
	std::string getCommandType(std::string);
	int getDeadlineSize(void);
	int getNormalSize(void);
	int getFloatingSize(void);
	std::vector<int> getColourIndex(void);
	Storage* getStorage(void);

private:
	Storage storage;
	Parser parser;
	NormalTask normTask;
	DeadlineTask deadlineTask;
	FloatingTask floatingTask;
	UndoTask undoTask;
	DeleteTask deleteTask;
	OverdueTask overdueTask;
	SearchTask searchTask;
	EditTask editTask;
	std::vector<CommandDetails*> commandDetails;

	static const std::string STRING_ADD;
	static const std::string STRING_ARCHIVE;
	static const std::string STRING_CD;
	static const std::string STRING_COMPLETE;
	static const std::string STRING_DISPLAY;
	static const std::string STRING_DELETE;
	static const std::string STRING_EDIT;
	static const std::string STRING_EXIT;
	static const std::string STRING_HELP;
	static const std::string STRING_INVALID;
	static const std::string STRING_NIL;
	static const std::string STRING_SEARCH;
	static const std::string STRING_UNDO;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, ERASE, SEARCH, EXIT, INVALID, UNDO, EDIT, COMPLETE, DISPLAY, CD, HELP
	};

	//SLAP level 2
	int createDynamicNewCommandDetails(void);
	std::string executeLogicCore(std::string);
	//SLAP level 3
	std::string determineParserCase(std::string, int);
	TASK_TYPE determineSpecificTaskType(int);
	bool lastCommandIsSearch(void);
	//SLAP level 4
	std::string executeTask(TASK_TYPE, int);
	std::string executeRecurringTask(std::string, int);

};


#endif