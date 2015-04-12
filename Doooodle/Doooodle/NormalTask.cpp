//@author A0108562H
#include "NormalTask.h"

NormalTask::NormalTask(void) {
	task = "";
	dateStart = day_clock::local_day();
	dateEnd = day_clock::local_day();
	timeStart = not_a_date_time;
	timeEnd = not_a_date_time;
}

NormalTask::~NormalTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string NormalTask::loadTask(std::string task, date dateStart, date dateEnd, ptime timeStart, ptime timeEnd, Storage& storage) {
	this->task = task;
	this->dateStart = dateStart;
	this->dateEnd = dateEnd;
	this->timeStart = timeStart;
	this->timeEnd = timeEnd;
	displayMessage = storage.addNormalTask(task, dateStart, dateEnd, timeStart, timeEnd);
	storage.sortStorage();
	storage.writeToFile();
	return displayMessage;
}