
#include "DeleteSearchTask.h"

DeleteSearchTask::DeleteSearchTask(void) {
}

DeleteSearchTask::~DeleteSearchTask(void) {
}

string DeleteSearchTask::loadTask(int intToDelete, Storage& storage){
	displayMessage =  storage.deleteSearchTask(intToDelete);
	storage.writeToFile();
	return displayMessage;
}
