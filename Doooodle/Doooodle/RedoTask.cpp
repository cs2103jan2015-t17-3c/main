
#include "RedoTask.h"

const string RedoTask::MESSAGE_ADD = "add";
const string RedoTask::MESSAGE_DELETE = "delete";
const string RedoTask::MESSAGE_EDIT = "edit";
const string RedoTask::MESSAGE_SEARCH = "search";
const string RedoTask::MESSAGE_UNDO = "undo";
const string RedoTask::MESSAGE_UNDO_FAILURE = "Nothing to redo!";

RedoTask::RedoTask(void) {
}

RedoTask::~RedoTask(void) {
}

string RedoTask::loadRedoTask(vector<CommandDetails*>& CD, Storage& storage) {
	TASK_TYPE taskType = retrieveTaskTypeToRedo(CD);
	string displayMessage;
	switch(taskType) {
	case NIL:
		displayMessage = MESSAGE_UNDO_FAILURE;
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
	return storage.undoAdd();
}

string RedoTask::executeRedoDelete(vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.undoDelete();
}

string RedoTask::executeRedoEdit(vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.undoEdit();
}

RedoTask::TASK_TYPE RedoTask::retrieveTaskTypeToRedo(vector<CommandDetails*>& CD) {
	int index = CD.size()-1;
	assert(index>=0);
	if (index<0) {
		return NIL;
	} 
	else if(CD[index]->commandType==MESSAGE_ADD) {
		return ADD;
	}
	else if(CD[index]->commandType==MESSAGE_DELETE) {
		return DELETE;
	}
	else if(CD[index]->commandType==MESSAGE_SEARCH) {
		CD.pop_back(); //search will not be undone, hence pop_back and recursion to retrieve next in line
		return retrieveTaskTypeToRedo(CD);
	}
	else if(CD[index]->commandType==MESSAGE_UNDO) {
		CD.pop_back(); //get rid of undo in CD
		return retrieveTaskTypeToRedo(CD);
	}
	else if(CD[index]->commandType==MESSAGE_EDIT) {
		return EDIT;
	}
	else { //for invalid cases
		CD.pop_back();
		return retrieveTaskTypeToRedo(CD);
	};
}
