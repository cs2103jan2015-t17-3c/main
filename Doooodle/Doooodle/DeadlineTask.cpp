
#include "DeadlineTask.h"

DeadlineTask::DeadlineTask(void) {
	task = "";
	dateEnd = boost::gregorian::day_clock::local_day();
	timeEnd = boost::posix_time::not_a_date_time;
}

DeadlineTask::~DeadlineTask(void) {
}

vector<string> DeadlineTask::loadDeadlineTask(string task, boost::gregorian::date dateEnd, boost::posix_time::ptime timeEnd, Storage& storage) {
	this->task = task;
	this->dateEnd = dateEnd;
	this->timeEnd = timeEnd;
<<<<<<< HEAD
	vector<string> displayMessageToLogic = storage.addDeadlineTask(task, dateEnd, timeEnd);
	storage.sortStorage();
=======
	string displayMessageToLogic = storage.addDeadlineTask(task, dateEnd, timeEnd);
	//storage.sortStorage();
>>>>>>> origin/master
	storage.writeToFile();
	return displayMessageToLogic;
}