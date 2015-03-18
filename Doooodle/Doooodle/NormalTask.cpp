
#include "NormalTask.h"

NormalTask::NormalTask(void) {
	task = "";
	dateStart = boost::gregorian::day_clock::local_day();
	dateEnd = boost::gregorian::day_clock::local_day();
	timeStart = boost::posix_time::not_a_date_time;
	timeEnd = boost::posix_time::not_a_date_time;
}

NormalTask::~NormalTask(void) {
}

vector<string> NormalTask::loadNormalTask(string task, boost::gregorian::date dateStart, boost::gregorian::date dateEnd, boost::posix_time::ptime timeStart, boost::posix_time::ptime timeEnd, Storage& storage) {
	this->task = task;
	this->dateStart = dateStart;
	this->dateEnd = dateEnd;
	this->timeStart = timeStart;
	this->timeEnd = timeEnd;
<<<<<<< HEAD
	vector<string> displayMessageToLogic = storage.addNormalTask(task, dateStart, dateEnd, timeStart, timeEnd);
	storage.sortStorage();
=======
	string displayMessageToLogic = storage.addNormalTask(task, dateStart, dateEnd, timeStart, timeEnd);
	//storage.sortStorage();
>>>>>>> origin/master
	storage.writeToFile();
	return displayMessageToLogic;
}