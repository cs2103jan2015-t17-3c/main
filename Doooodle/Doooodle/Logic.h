
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
#include "UndoTask.h"
#include "DeleteTask.h"
#include "SearchTask.h"
#include "EditTask.h"
#include "RescheduleTask.h"
#include "OverdueTask.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class Logic {

public:
	Logic(void);
	~Logic(void);
	std::string receiveCommand(std::string);
	std::vector<std::string> displayTopTen(void);
	std::vector<std::string> displayFloatingTask(void);
	std::vector<std::string> displaySearchResults(std::string);
	std::vector<std::string> displayOverdue(void);
	std::vector<std::string> displayCategoricalTask(std::string, std::string&);
	std::string getCommandType(std::string);
	int getDeadlineSize(void);
	int getNormalSize(void);
	int getFloatingSize(void);
	Storage* getStorage(void);

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
	static const std::string STRING_ADD;
	static const std::string STRING_ARCHIVE;
	static const std::string STRING_CHECK;
	static const std::string STRING_COMPLETE;
	static const std::string STRING_COMPLETED;
	static const std::string STRING_DISPLAY;

	static const std::string STRING_DELETE;
	static const std::string STRING_EDIT;
	static const std::string STRING_EXIT;
	static const std::string STRING_INVALID;
	static const std::string STRING_RESCHEDULE;
	static const std::string STRING_SEARCH;
	static const std::string STRING_UNDO;
	static const int TOP10MAX;
	static const int FLOATMAX;

	std::vector<CommandDetails*> commandDetails;

	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, ERASE, SEARCH, EXIT, INVALID, UNDO, EDIT, CHECK, RESCHEDULE, COMPLETE, COMPLETED, DISPLAY
	};

	std::string executeLogicCore(std::string);
	std::string executeTask(TASK_TYPE, int);
	std::string executeRecurringTask(std::string, int);
	TASK_TYPE determineSpecificTaskType(int);
	bool lastCommandIsSearch(void);
};


#endif