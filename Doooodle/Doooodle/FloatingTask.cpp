
#include "FloatingTask.h"

FloatingTask::FloatingTask(void) {
	task = "";
}

FloatingTask::~FloatingTask(void) {
}

vector<string> FloatingTask::loadFloatingTask(string task, Storage& storage) {
	this->task = task;
<<<<<<< HEAD
	vector<string> displayMessageToLogic = storage.addFloatTask(task);
	storage.sortStorage();
=======
	string displayMessageToLogic = storage.addFloatTask(task);
	//storage.sortStorage();
>>>>>>> origin/master
	storage.writeToFile();
	return displayMessageToLogic;
}