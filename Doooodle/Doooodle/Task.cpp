
#include "Task.h"

const string Task::STRING_TEMPLATE = "Super Class";

Task::Task(void) {
	task = "";
	dateStart = boost::gregorian::day_clock::local_day();
	dateEnd = boost::gregorian::day_clock::local_day();
	timeStart = boost::posix_time::not_a_date_time;
	timeEnd = boost::posix_time::not_a_date_time;
}

Task::~Task(void) {
}

string Task::loadTask(string task, Storage& storage) {
	this->task = task;
	return STRING_TEMPLATE;
}