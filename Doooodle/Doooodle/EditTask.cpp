
#include "EditTask.h"

EditTask::EditTask(void) {
}

EditTask::~EditTask(void) {
}

//overwrite ITask and calls appropriate storage public API
std::string EditTask::loadTask(int index, std::string stringToEdit, date startDate, date endDate, ptime startTime, ptime endTime, Storage& storage){
	displayMessage = storage.editTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}

//method is called when last search command is "search" to delete search result
std::string EditTask::editSearchTask(int index, std::string stringToEdit, date startDate, date endDate, ptime startTime, ptime endTime, Storage& storage){
	displayMessage = storage.editSearchTask(index, stringToEdit, startDate, endDate, startTime, endTime);
	storage.sortStorage();
	storage.writeToFile();
	assert(!(displayMessage.empty()));
	return displayMessage;
}