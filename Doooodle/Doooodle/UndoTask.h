
#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include <iostream>
#include "ITask.h"
#include "CommandDetails.h"

using namespace std;

class UndoTask : public ITask {

public:
	UndoTask(void);
	~UndoTask(void);
	string loadTask(vector<CommandDetails*>&, vector<CommandDetails*>&, Storage&);

private:
	enum TASK_TYPE {
		ADD, DELETE, EDIT, NIL
	};
	static const string STRING_ADD;
	static const string STRING_DELETE;
	static const string STRING_EDIT;
	static const string STRING_UNDO_FAILURE;
	static const string STRING_SEARCH;
	static const string STRING_UNDO;

	TASK_TYPE retrieveTaskTypeToUndo(vector<CommandDetails*>&);
	string executeUndoAdd(vector<CommandDetails*>&, vector<CommandDetails*>&, Storage&);
	string executeUndoDelete(vector<CommandDetails*>&, vector<CommandDetails*>&, Storage&);
	string executeUndoEdit(vector<CommandDetails*>&, vector<CommandDetails*>&, Storage&);
};

#endif