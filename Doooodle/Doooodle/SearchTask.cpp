
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

vector<string> SearchTask::loadTask(string stringToSearch, boost::gregorian::date dateToSearch, boost::posix_time::ptime timeToSearch, Storage& storage){
	vector<string> displayMessage;
	displayMessage = storage.searchTask(stringToSearch, dateToSearch, timeToSearch);
	assert(displayMessage.size()>=0);
	return displayMessage;
}
