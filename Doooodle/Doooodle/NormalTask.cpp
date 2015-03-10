
#include "NormalTask.h"

NormalTask::NormalTask(void) {
	task = "";
	timeStart = "";
	timeEnd = "";
}

NormalTask::~NormalTask(void) {
}

string NormalTask::loadNormalTask(string task, string timeStart, string timeEnd, Storage& storage) {
	this->task = task;
	this->timeStart = timeStart;
	this->timeEnd = timeEnd;
	string displayMessageToLogic = storage.addNormalTask(task, timeStart, timeEnd);
	return displayMessageToLogic;
}