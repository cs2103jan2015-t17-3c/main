
#include "DeleteSearchTask.h"

DeleteSearchTask::DeleteSearchTask(void) {
}

DeleteSearchTask::~DeleteSearchTask(void) {
}

string DeleteTask::loadDeleteTask(int intToDelete, Storage& storage){
	string displayMessage =  storage.deleteSearchTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}
