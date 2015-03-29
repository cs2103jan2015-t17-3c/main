
#include "Logic.h"

const string Logic::STRING_ADD = "add";
const string Logic::STRING_ARCHIVE = "archive";
const string Logic::STRING_CHECK = "check";
const string Logic::STRING_COMPLETE = "complete";
const string Logic::STRING_COMPLETED = "completed";
const string Logic::STRING_DISPLAY = "display";
const string Logic::STRING_DELETE = "delete";
const string Logic::STRING_EDIT = "edit";
const string Logic::STRING_EXIT = "exit";
const string Logic::STRING_INVALID = "ERROR!";
const string Logic::STRING_RESCHEDULE = "reschedule";
const string Logic::STRING_SEARCH = "search";
const string Logic::STRING_UNDO = "undo";
const int Logic::TOP10MAX = 10;
const int Logic::FLOATMAX = 5;

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

vector<string> Logic::displayTopTen(void) {
	vector<string> topTenToDisplay = storage.retrieveTopTen();
	assert(topTenToDisplay.size()<=TOP10MAX);
	return topTenToDisplay; 
}

vector<string> Logic::displayFloatingTask(void) {
	vector<string> floatingTask = storage.retrieveFloatingTask();
	assert(floatingTask.size()<=FLOATMAX);
	return floatingTask; 
}

vector<string> Logic::displayOverdue(void) {
	vector<string> overdue = storage.retrieveOverdue();
	return overdue;
}

vector<string> Logic::displaySearchResults(string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	assert(commandDetails[index]->commandType==STRING_SEARCH);
	return searchTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateEnd, commandDetails[index]->timeEnd, storage);
}

vector<string> Logic::displayCategoricalTask(string userInput, string& taskType) {
	int index = commandDetails.size();
	vector<string> categoricalTask;
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	taskType = commandDetails[index]->task;
	categoricalTask = storage.retrieveCategoricalTask(taskType);
	return categoricalTask;
}

string Logic::getCommandType(string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	string lastCommand = commandDetails[index]->commandType;
	commandDetails.pop_back();
	return lastCommand;
}


string Logic::receiveCommand(string userInput) {
	string displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

string Logic::executeLogicCore(string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart ,commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	TASK_TYPE taskType = determineSpecificTaskType(index);
	return executeTask(taskType, index);
}

string Logic::executeTask(TASK_TYPE taskType, int index) {
	string displayMessageToUI;
	switch(taskType) {
	case NORMAL:
		displayMessageToUI = normTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateStart ,commandDetails[index]->dateEnd, commandDetails[index]->timeStart ,commandDetails[index]->timeEnd, storage);
		break;
	case DEADLINE:
		displayMessageToUI = deadlineTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateEnd, commandDetails[index]->timeEnd, storage);
		break;
	case FLOATING:
		displayMessageToUI = floatingTask.loadTask(commandDetails[index]->task, storage);
		break;
	case DELETE:
		if (lastCommandIsSearch()) {
			displayMessageToUI = deleteTask.deleteSearchTask(commandDetails[index]->indexReference, storage);
		}
		else{
			displayMessageToUI = deleteTask.loadTask(commandDetails[index]->indexReference, storage);
		}
		break;
	case SEARCH:
		displayMessageToUI = " ";
		break;
	case EXIT:
		exit(0);
		break;
	case UNDO:
		displayMessageToUI = undoTask.loadTask(commandDetails, storage);
		break;
	case EDIT:
		if (lastCommandIsSearch()) {
			displayMessageToUI = editTask.editSearchTask(commandDetails[index]->indexReference, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, storage);
		}
		else{
			displayMessageToUI = editTask.loadTask(commandDetails[index]->indexReference, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, storage);
		}
		break;
	case RESCHEDULE:
		displayMessageToUI = rescheduleTask.loadTask(commandDetails[index]->indexReference, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, storage);
		break;
	case CHECK:
		displayMessageToUI = " ";
		break;
	case COMPLETE:
		if (lastCommandIsSearch()) {
			displayMessageToUI = overdueTask.completeSearchTask(commandDetails[index]->indexReference, storage);
		}
		else{
			displayMessageToUI = overdueTask.completeTask(commandDetails[index]->indexReference, storage);
		}
		break;
	case COMPLETED:
		displayMessageToUI = overdueTask.loadTask(storage);
		break;
	case INVALID:
		displayMessageToUI = STRING_INVALID;
		break;
	} 
	assert(!displayMessageToUI.empty());
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int index) {
	boost::gregorian::date dateNull(boost::date_time::not_a_date_time);
	if(commandDetails[index]->commandType==STRING_ADD) {
		if((commandDetails[index]->timeEnd==boost::posix_time::not_a_date_time) && (commandDetails[index]->dateEnd==dateNull)) {
			return FLOATING;
		}
		else if((commandDetails[index]->timeStart==boost::posix_time::not_a_date_time) && (commandDetails[index]->dateStart==dateNull)) {
			return DEADLINE;
		}
		else {
			return NORMAL;
		}
	}
	else if(commandDetails[index]->commandType==STRING_DELETE) {
		return DELETE;
	}
	else if(commandDetails[index]->commandType==STRING_SEARCH) {
		return SEARCH;
	}
	else if(commandDetails[index]->commandType==STRING_EXIT) {
		return EXIT;
	}
	else if(commandDetails[index]->commandType==STRING_UNDO) {
		return UNDO;
	}
	else if(commandDetails[index]->commandType==STRING_EDIT) {
		return EDIT;
	}
	else if (commandDetails[index]->commandType == STRING_CHECK) {
		return CHECK;
	}
	else if (commandDetails[index]->commandType == STRING_RESCHEDULE) {
		return RESCHEDULE;
	}
	else if (commandDetails[index]->commandType == STRING_COMPLETE) {
		return COMPLETE;
	}
	else if (commandDetails[index]->commandType == STRING_COMPLETED) {
		return COMPLETED;
	}
	else return INVALID;
}

bool Logic::lastCommandIsSearch(void) {
	int index = commandDetails.size()-2;
	return (commandDetails[index]->commandType==STRING_SEARCH);
}