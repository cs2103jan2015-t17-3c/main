
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
	static const string STRING_ADD;
	static const string STRING_DELETE;
	static const string STRING_EDIT;
	static const string STRING_UNDO_FAILURE;

	TASK_TYPE retrieveTaskTypeToRedo(vector<CommandDetails*>&);
	string executeRedoAdd(vector<CommandDetails*>&, Storage&);
	string executeRedoDelete(vector<CommandDetails*>&, Storage&);
	string executeRedoEdit(vector<CommandDetails*>&, Storage&);
};

#endif