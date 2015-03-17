
#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <boost/date_time.hpp>
#include "Storage.h"
#include "CommandDetails.h"

using namespace std;

class UndoTask {

public:
	UndoTask(void);
	~UndoTask(void);
	vector<string> loadUndoTask(vector<CommandDetails*>, Storage&);

private:
	enum TASK_TYPE {
		ADD, DELETE, EDIT, NIL
	};
	string task;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

	TASK_TYPE retrieveTaskTypeToUndo(vector<CommandDetails*>);
	vector<string> executeUndoAdd(vector<CommandDetails*>, Storage&);
	vector<string> executeUndoDelete(vector<CommandDetails*>, Storage&);
	vector<string> executeUndoEdit(vector<CommandDetails*>, Storage&);
};

#endif