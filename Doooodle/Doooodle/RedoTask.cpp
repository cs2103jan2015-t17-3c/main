
#include "RedoTask.h"

const string RedoTask::STRING_ADD = "add";
const string RedoTask::STRING_DELETE = "delete";
const string RedoTask::STRING_EDIT = "edit";
const string RedoTask::STRING_UNDO_FAILURE = "Nothing to redo!";

RedoTask::RedoTask(void) {
}

RedoTask::~RedoTask(void) {
}

string RedoTask::loadRedoTask(vector<CommandDetails*>& CD, Storage& storage) {
	TASK_TYPE taskType = retrieveTaskTypeToRedo(CD);
	string displayMessage;
	switch(taskType) {
	case NIL:
		displayMessage = STRING_UNDO_FAILURE;
		break;
	case ADD:
		displayMessage = executeRedoAdd(CD, storage);
		break;
	case DELETE:
		displayMessage = executeRedoDelete(CD, storage);
		break;
	case EDIT:
		displayMessage = executeRedoEdit(CD, storage);
		break;
	}

	return displayMessage;
}

string RedoTask::executeRedoAdd(vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.redoAdd();
}

string RedoTask::executeRedoDelete(vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.redoDelete();
}

string RedoTask::executeRedoEdit(vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.redoEdit();
}

RedoTask::TASK_TYPE RedoTask::retrieveTaskTypeToRedo(vector<CommandDetails*>& CD) {
	int index = CD.size()-1;
	//use exception
	if (index<0) {
		return NIL;
	} 
	else if(CD[index]->commandType==STRING_ADD) {
		return ADD;
	}
	else if(CD[index]->commandType==STRING_DELETE) {
		return DELETE;
	}
	else if(CD[index]->commandType==STRING_EDIT) {
		return EDIT;
	}
	else { //should not come here
		assert(false);
	};
}
