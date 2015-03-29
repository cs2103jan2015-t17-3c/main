
#include "RescheduleTask.h"

RescheduleTask::RescheduleTask(void) {
}

RescheduleTask::~RescheduleTask(void) {
}

string RescheduleTask::loadTask(int index, boost::gregorian::date startDate, boost::gregorian::date endDate, boost::posix_time::ptime startTime, boost::posix_time::ptime endTime, Storage& storage){
	displayMessage = storage.reschedule(index, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
