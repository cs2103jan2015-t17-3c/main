
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

string loadEditTask(int intToDelete, Storage& storage){
	string displayMessage =  storage.deleteTask(intToDelete);
	storage.writeToFile;
	return displayMessage;
}
