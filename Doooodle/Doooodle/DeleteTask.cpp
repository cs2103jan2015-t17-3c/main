
#include "DeleteTask.h"

DeleteTask::DeleteTask(void) {
}

DeleteTask::~DeleteTask(void) {
}

std::string DeleteTask::loadTask(int intToDelete, Storage& storage){
	displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}

std::string DeleteTask::deleteSearchTask(int intToDelete, Storage& storage){
	displayMessage = storage.deleteSearchTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}