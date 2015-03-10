
#include "NormalTask.h"

NormalTask::NormalTask(void) {
	task = "";
	timeStart = "";
	timeEnd = "";
}

NormalTask::~NormalTask(void) {
}

void NormalTask::loadNormalTask(string task, string timeStart, string timeEnd, Storage& storage) {
	this->task = task;
	this->timeStart = timeStart;
	this->timeEnd = timeEnd;
	storage.addNormalTask(task, timeStart, timeEnd);
}