
#include "FloatingTask.h"

FloatingTask::FloatingTask(void) {
	task = "";
}

FloatingTask::~FloatingTask(void) {
}

string FloatingTask::loadFloatingTask(string task, Storage& storage) {
	this->task = task;
	string displayMessageToLogic = storage.addNormalTask(task);
	return displayMessageToLogic;
}