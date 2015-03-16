
#include "DeleteTask.h"

DeleteTask::DeleteTask(void) {
}

DeleteTask::~DeleteTask(void) {
}

string loadDeleteTask(int intToDelete, Storage& storage){
	string displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}
