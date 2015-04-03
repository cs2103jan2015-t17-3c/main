
#include "DeadlineTask.h"

DeadlineTask::DeadlineTask(void) {
	task = "";
	dateEnd = day_clock::local_day();
	timeEnd = not_a_date_time;
}

DeadlineTask::~DeadlineTask(void) {
}

std::string DeadlineTask::loadTask(std::string task, date dateEnd, ptime timeEnd, Storage& storage) {
	this->task = task;
	this->dateEnd = dateEnd;
	this->timeEnd = timeEnd;
	displayMessage = storage.addDeadlineTask(task, dateEnd, timeEnd);
	storage.sortStorage();
	storage.writeToFile();
	return displayMessage;
}