
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

vector<string> SearchTask::loadSearchTask(string stringToSearch, Storage& storage){
	vector<string> displayMessage;
	displayMessage = storage.searchTask(stringToSearch);
	return displayMessage;
}
