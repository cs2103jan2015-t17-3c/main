
#include "DeadlineTask.h"

DeadlineTask::DeadlineTask(void) {
	task = "";
	dateEnd = boost::gregorian::day_clock::local_day();
	timeEnd = boost::posix_time::not_a_date_time;
}

DeadlineTask::~DeadlineTask(void) {
}

string DeadlineTask::loadDeadlineTask(string task, boost::gregorian::date dateEnd, boost::posix_time::ptime timeEnd, Storage& storage) {
	this->task = task;
	this->dateEnd = dateEnd;
	this->timeEnd = timeEnd;
	string displayMessageToLogic = storage.addDeadlineTask(task, dateEnd, timeEnd);
	storage.sortStorage();
	return displayMessageToLogic;
}