//@author A0108562H
#include "DeleteTask.h"

DeleteTask::DeleteTask(void) {
}

DeleteTask::~DeleteTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string DeleteTask::loadTask(int intToDelete, Storage& storage){
	displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}

//method is called when last search command is "search" to delete search result
std::string DeleteTask::deleteSearchTask(int intToDelete, Storage& storage){
	displayMessage = storage.deleteSearchTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}