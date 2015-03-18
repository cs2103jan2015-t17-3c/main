
#include "UndoTask.h"

const string UndoTask::MESSAGE_ADD = "add";
const string UndoTask::MESSAGE_DELETE = "delete";
const string UndoTask::MESSAGE_EDIT = "edit";
const string UndoTask::MESSAGE_SEARCH = "search";
const string UndoTask::MESSAGE_UNDO = "undo";
const string UndoTask::MESSAGE_UNDO_FAILURE = "Nothing to undo!";

UndoTask::UndoTask(void) {
}

UndoTask::~UndoTask(void) {
}

vector<string> UndoTask::loadUndoTask(vector<CommandDetails*> CD, Storage& storage) {
	TASK_TYPE taskType = retrieveTaskTypeToUndo(CD);
	vector<string> displayMessage;
	switch(taskType) {
	case NIL:
		displayMessage.push_back(MESSAGE_UNDO_FAILURE);
		break;
	case ADD:
		displayMessage = executeUndoAdd(CD, storage);
		break;
	case DELETE:
		displayMessage = executeUndoDelete(CD, storage);
		break;
	case EDIT:
		displayMessage = executeUndoEdit(CD, storage);
		break;
	}

	return displayMessage;
}

vector<string> UndoTask::executeUndoAdd(vector<CommandDetails*> CD, Storage& storage) {
	CD.pop_back();
	return storage.undoAdd();
}

vector<string> UndoTask::executeUndoDelete(vector<CommandDetails*> CD, Storage& storage) {
	CD.pop_back();
	storage.undoDelete();
}

vector<string> UndoTask::executeUndoEdit(vector<CommandDetails*> CD, Storage& storage) {
	CD.pop_back();
	storage.undoEdit();
}

UndoTask::TASK_TYPE UndoTask::retrieveTaskTypeToUndo(vector<CommandDetails*> CD) {
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
		return retrieveTaskTypeToUndo(CD);
	}
	else if(CD[index]->commandType==MESSAGE_UNDO) {
		CD.pop_back(); //get rid of undo in CD
		return retrieveTaskTypeToUndo(CD);
	}
	else if(CD[index]->commandType==MESSAGE_EDIT) {
		return EDIT;
	}
	else { //for invalid cases
		CD.pop_back();
		return retrieveTaskTypeToUndo(CD);
	};
}
