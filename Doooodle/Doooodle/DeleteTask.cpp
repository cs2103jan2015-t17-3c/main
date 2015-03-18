
#include "DeleteTask.h"

DeleteTask::DeleteTask(void) {
}

DeleteTask::~DeleteTask(void) {
}

vector<string> DeleteTask::loadDeleteTask(int intToDelete, Storage& storage){
	vector<string> displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}
