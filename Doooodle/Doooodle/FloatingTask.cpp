
#include "FloatingTask.h"

FloatingTask::FloatingTask(void) {
	task = "";
}

FloatingTask::~FloatingTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string FloatingTask::loadTask(std::string task, Storage& storage) {
	this->task = task;
	displayMessage = storage.addFloatingTask(task);
	storage.sortStorage();
	storage.writeToFile();
	return displayMessage;
}