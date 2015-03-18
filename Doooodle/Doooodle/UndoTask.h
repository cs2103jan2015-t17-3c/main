
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
	string loadUndoTask(vector<CommandDetails*>&, Storage&);

private:
	enum TASK_TYPE {
		ADD, DELETE, EDIT, NIL
	};
	static const string MESSAGE_ADD;
	static const string MESSAGE_DELETE;
	static const string MESSAGE_EDIT;
	static const string MESSAGE_UNDO_FAILURE;
	static const string MESSAGE_SEARCH;
	static const string MESSAGE_UNDO;

	TASK_TYPE retrieveTaskTypeToUndo(vector<CommandDetails*>&);
	string executeUndoAdd(vector<CommandDetails*>&, Storage&);
	string executeUndoDelete(vector<CommandDetails*>&, Storage&);
	string executeUndoEdit(vector<CommandDetails*>&, Storage&);
};

#endif