
#include "UndoTask.h"

string UndoTask::loadUndoTask(vector<CommandDetails*> CD, Storage&) {
	TASK_TYPE undoType = retrieveTaskTypeToUndo(CD);

	return " ";
}
