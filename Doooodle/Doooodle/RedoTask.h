
#ifndef REDOTASK_H_
#define REDOTASK_H_

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <boost/date_time.hpp>
#include "Storage.h"
#include "CommandDetails.h"

using namespace std;

class RedoTask {

public:
	RedoTask(void);
	~RedoTask(void);
	string loadRedoTask(vector<CommandDetails*>&, Storage&);

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

	TASK_TYPE retrieveTaskTypeToRedo(vector<CommandDetails*>&);
	string executeRedoAdd(vector<CommandDetails*>&, Storage&);
	string executeRedoDelete(vector<CommandDetails*>&, Storage&);
	string executeRedoEdit(vector<CommandDetails*>&, Storage&);
};

#endif