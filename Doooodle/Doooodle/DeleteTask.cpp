
#include "DeleteTask.h"

DeleteTask::DeleteTask(void) {
}

DeleteTask::~DeleteTask(void) {
}

string DeleteTask::loadTask(int intToDelete, Storage& storage){
	displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}
