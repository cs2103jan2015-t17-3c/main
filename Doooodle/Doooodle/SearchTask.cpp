
#include "SearchTask.h"

SearchTask::SearchTask(void) {
}

SearchTask::~SearchTask(void) {
}

string SearchTask::loadSearchTask(string stringToSearch, Storage& storage){
	string displayMessage = storage.searchTask(stringToSearch);
	storage.writeToFile;
	return displayMessage;
}
