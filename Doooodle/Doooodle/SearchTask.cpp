
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

vector<string> SearchTask::loadTask(string stringToSearch, Storage& storage){
	vector<string> displayMessage;
	displayMessage = storage.searchTask(stringToSearch);
	assert(displayMessage.size()>=0);
	return displayMessage;
}
