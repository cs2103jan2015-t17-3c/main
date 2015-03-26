
#include "EditSearchTask.h"

EditSearchTask::EditSearchTask(void) {
}

EditSearchTask::~EditSearchTask(void) {
}

string EditSearchTask::loadTask(int index, string stringToEdit, boost::gregorian::date startDate, boost::gregorian::date endDate, boost::posix_time::ptime startTime, boost::posix_time::ptime endTime, Storage& storage){
	displayMessage = storage.editSearchTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
