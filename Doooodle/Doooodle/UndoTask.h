
#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include <iostream>
#include <vector>
#include <string>
#include <boost/date_time.hpp>
#include "Storage.h"
#include "CommandDetails.h"

using namespace std;

class UndoTask {

public:
	UndoTask(void);
	~UndoTask(void);
	string loadUndoTask(vector<CommandDetails*>, Storage&);

private:
	enum TASK_TYPE {
		DEADLINE, FLOATING, NORMAL, DELETE, SEARCH, EXIT, INVALID, UNDO, EDIT
	};
	string task;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

	TASK_TYPE retrieveTaskTypeToUndo(vector<CommandDetails*>);
};

#endif