
#include "UndoTask.h"

UndoTask::UndoTask(void) {
}

UndoTask::~UndoTask(void) {
}

string UndoTask::loadUndoTask(vector<CommandDetails*> CD, Storage&) {
	TASK_TYPE undoType = retrieveTaskTypeToUndo(CD);

	return " ";
}
