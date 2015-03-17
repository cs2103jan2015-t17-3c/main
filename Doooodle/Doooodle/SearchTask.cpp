
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

vector<string> SearchTask::loadSearchTask(string stringToSearch, Storage& storage){
	vector<string> displayMessage;
	displayMessage.push_back(storage.searchTask(stringToSearch));
	storage.writeToFile;
	return displayMessage;
}
