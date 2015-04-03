
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

std::string EditTask::loadTask(int index, std::string stringToEdit, date startDate, date endDate, ptime startTime, ptime endTime, Storage& storage){
	displayMessage = storage.editTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

std::string EditTask::editSearchTask(int index, std::string stringToEdit, date startDate, date endDate, ptime startTime, ptime endTime, Storage& storage){
	displayMessage = storage.editSearchTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}