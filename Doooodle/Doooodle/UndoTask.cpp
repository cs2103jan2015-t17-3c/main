
#include "UndoTask.h"

const string UndoTask::STRING_ADD = "add";
const string UndoTask::STRING_DELETE = "delete";
const string UndoTask::STRING_EDIT = "edit";
const string UndoTask::STRING_SEARCH = "search";
const string UndoTask::STRING_UNDO = "undo";
const string UndoTask::STRING_UNDO_FAILURE = "Nothing to undo!";

UndoTask::UndoTask(void) {
}

UndoTask::~UndoTask(void) {
}

string UndoTask::loadTask(vector<CommandDetails*>& CD, vector<CommandDetails*>& CDforRedo, Storage& storage) {
	TASK_TYPE taskType = retrieveTaskTypeToUndo(CD);
	string displayMessage;
	switch(taskType) {
	case NIL:
		displayMessage = STRING_UNDO_FAILURE;
		break;
	case ADD:
		displayMessage = executeUndoAdd(CD, CDforRedo, storage);
		break;
	case DELETE:
		displayMessage = executeUndoDelete(CD, CDforRedo, storage);
		break;
	case EDIT:
		displayMessage = executeUndoEdit(CD, CDforRedo, storage);
		break;
	}

	return displayMessage;
}

string UndoTask::executeUndoAdd(vector<CommandDetails*>& CD, vector<CommandDetails*>& CDforRedo, Storage& storage) {
	CDforRedo.push_back(CD[CD.size()-1]);
	CD.pop_back();
	return storage.undoAdd();
}

string UndoTask::executeUndoDelete(vector<CommandDetails*>& CD, vector<CommandDetails*>& CDforRedo, Storage& storage) {
	CDforRedo.push_back(CD[CD.size()-1]);
	CD.pop_back();
	return storage.undoDelete();
}

string UndoTask::executeUndoEdit(vector<CommandDetails*>& CD, vector<CommandDetails*>& CDforRedo, Storage& storage) {
	CDforRedo.push_back(CD[CD.size()-1]);
	CD.pop_back();
	return storage.undoEdit();
}

UndoTask::TASK_TYPE UndoTask::retrieveTaskTypeToUndo(vector<CommandDetails*>& CD) {
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
	else if(CD[index]->commandType==STRING_SEARCH) {
		CD.pop_back(); //search will not be undone, hence pop_back and recursion to retrieve next in line
		return retrieveTaskTypeToUndo(CD);
	}
	else if(CD[index]->commandType==STRING_UNDO) {
		CD.pop_back(); //get rid of undo in CD
		return retrieveTaskTypeToUndo(CD);
	}
	else if(CD[index]->commandType==STRING_EDIT) {
		return EDIT;
	}
	else { //for invalid cases
		CD.pop_back();
		return retrieveTaskTypeToUndo(CD);
	};
}
