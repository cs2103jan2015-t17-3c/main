
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

string EditTask::loadTask(int intToDelete, Storage& storage){
	string displayMessage;
	//displayMessage.push_back(storage.deleteTask(intToDelete));
	storage.writeToFile();
	return displayMessage;
}
