
#include "UndoTask.h"

const std::string UndoTask::STRING_ADD = "add";
const std::string UndoTask::STRING_DELETE = "delete";
const std::string UndoTask::STRING_EDIT = "edit";
const std::string UndoTask::STRING_SEARCH = "search";
const std::string UndoTask::STRING_UNDO = "undo";
const std::string UndoTask::STRING_UNDO_FAILURE = "Nothing to undo!";

UndoTask::UndoTask(void) {
}

UndoTask::~UndoTask(void) {
}

std::string UndoTask::loadTask(std::vector<CommandDetails*>& CD, Storage& storage) {
	TASK_TYPE taskType = retrieveTaskTypeToUndo(CD);
	switch(taskType) {
	case NIL:
		displayMessage = STRING_UNDO_FAILURE;
		break;
	case ADD:
		displayMessage = executeUndoAdd(CD, storage);
		break;
	case ERASE:
		displayMessage = executeUndoDelete(CD, storage);
		break;
	case EDIT:
		displayMessage = executeUndoEdit(CD, storage);
		break;
	}
	storage.sortStorage();
	storage.writeToFile();
	return displayMessage;
}

std::string UndoTask::executeUndoAdd(std::vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.undoAdd();
}

std::string UndoTask::executeUndoDelete(std::vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.undoDelete();
}

std::string UndoTask::executeUndoEdit(std::vector<CommandDetails*>& CD, Storage& storage) {
	CD.pop_back();
	return storage.undoEdit();
}

UndoTask::TASK_TYPE UndoTask::retrieveTaskTypeToUndo(std::vector<CommandDetails*>& CD) {
	int index = CD.size()-1;
	//use exception
	if (index<0) {
		return NIL;
	} 
	else if(CD[index]->commandType==STRING_ADD) {
		return ADD;
	}
	else if(CD[index]->commandType==STRING_DELETE) {
		return ERASE;
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
