
#include "OverdueTask.h"

OverdueTask::OverdueTask(void) {
}

OverdueTask::~OverdueTask(void) {
}

string OverdueTask::loadTask(Storage& storage){
	displayMessage = storage.completeAll();
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

string OverdueTask::completeTask(int intToComplete, Storage& storage) {
	displayMessage = storage.completeTask(intToComplete);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

string OverdueTask::completeSearchTask(int intToComplete, Storage& storage) {
	displayMessage = storage.completeSearchTask(intToComplete);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
