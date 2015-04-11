
#include "RescheduleTask.h"

RescheduleTask::RescheduleTask(void) {
}

RescheduleTask::~RescheduleTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string RescheduleTask::loadTask(int index, date startDate, date endDate, ptime startTime, ptime endTime, Storage& storage){
	displayMessage = storage.reschedule(index, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}
