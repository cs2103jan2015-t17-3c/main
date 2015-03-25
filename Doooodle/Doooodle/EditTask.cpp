
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

string EditTask::loadTask(int index, string stringToEdit, boost::gregorian::date startDate, boost::gregorian::date endDate, boost::posix_time::ptime startTime, boost::posix_time::ptime endTime, Storage& storage){
	displayMessage = storage.editTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
