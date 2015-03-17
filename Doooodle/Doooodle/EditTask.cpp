
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

vector<string> EditTask::loadEditTask(int intToDelete, Storage& storage){
	vector<string> displayMessage;
	displayMessage.push_back(storage.deleteTask(intToDelete));
	storage.writeToFile;
	return displayMessage;
}
