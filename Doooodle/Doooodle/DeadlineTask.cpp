
#include "DeadlineTask.h"

DeadlineTask::DeadlineTask(void) {
	task = "";
	timeEnd = "";
}

DeadlineTask::~DeadlineTask(void) {
}

string DeadlineTask::loadDeadlineTask(string task, string timeEnd, Storage& storage) {
	this->task = task;
	this->timeEnd = timeEnd;
	string displayMessageToLogic = storage.addDeadlineTask(task, timeEnd);
	return displayMessageToLogic;
}