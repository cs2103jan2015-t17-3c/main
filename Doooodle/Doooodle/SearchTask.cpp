
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

std::vector<std::string> SearchTask::loadTask(std::string stringToSearch, date dateToSearch, ptime timeToSearch, Storage& storage){
	std::vector<std::string> displayMessage;
	displayMessage = storage.searchTask(stringToSearch, dateToSearch, timeToSearch);
	assert(displayMessage.size()>=0);
	return displayMessage;
}
