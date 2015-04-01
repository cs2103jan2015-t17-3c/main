
#include "FloatingTask.h"

FloatingTask::FloatingTask(void) {
	task = "";
}

FloatingTask::~FloatingTask(void) {
}

string FloatingTask::loadTask(string task, Storage& storage) {
	this->task = task;
	displayMessage = storage.addFloatingTask(task);
	storage.sortStorage();
	storage.writeToFile();
	return displayMessage;
}