
#include "OverdueTask.h"

OverdueTask::OverdueTask(void) {
}

OverdueTask::~OverdueTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string OverdueTask::loadTask(Storage& storage){
	displayMessage = storage.completeAll();
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

//method is called on completion of task in the TopList
std::string OverdueTask::completeTask(int intToComplete, Storage& storage) {
	displayMessage = storage.completeTask(intToComplete);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

//method is called when last search command is "search" to delete search result
std::string OverdueTask::completeSearchTask(int intToComplete, Storage& storage) {
	displayMessage = storage.completeSearchTask(intToComplete);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
