
#include "Logic.h"

const std::string Logic::STRING_ADD = "add";
const std::string Logic::STRING_ARCHIVE = "archive";
const std::string Logic::STRING_CD = "cd";
const std::string Logic::STRING_CHECK = "check";
const std::string Logic::STRING_COMPLETE = "complete";
const std::string Logic::STRING_COMPLETED = "completed";
const std::string Logic::STRING_DISPLAY = "display";
const std::string Logic::STRING_DELETE = "delete";
const std::string Logic::STRING_EDIT = "edit";
const std::string Logic::STRING_EXIT = "exit";
const std::string Logic::STRING_INVALID = "ERROR!";
const std::string Logic::STRING_RESCHEDULE = "reschedule";
const std::string Logic::STRING_SEARCH = "search";
const std::string Logic::STRING_UNDO = "undo";
const int Logic::TOP15MAX = 15;
const int Logic::FLOATMAX = 5;

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

std::vector<std::string> Logic::displayTopFifteen(void) {
	std::vector<std::string> topTenToDisplay = storage.retrieveTopFifteen();
	//assert(topTenToDisplay.size()<=TOP15MAX);
	return topTenToDisplay; 
}

std::vector<std::string> Logic::displayFloatingTask(void) {
	std::vector<std::string> floatingTask = storage.retrieveFloatingTask();
	assert(floatingTask.size()<=FLOATMAX);
	return floatingTask; 
}

std::vector<std::string> Logic::displayOverdue(void) {
	std::vector<std::string> overdue = storage.retrieveOverdue();
	return overdue;
}

std::vector<std::string> Logic::displaySearchResults(std::string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	assert(commandDetails[index]->commandType==STRING_SEARCH);
	return searchTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateEnd, commandDetails[index]->timeEnd, storage);
}

std::vector<std::string> Logic::displayCategoricalTask(std::string userInput, std::string& taskType) {
	int index = commandDetails.size();
	std::vector<std::string> categoricalTask;
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	taskType = commandDetails[index]->task;
	categoricalTask = storage.retrieveCategoricalTask(taskType);
	return categoricalTask;
}

std::string Logic::getCommandType(std::string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	std::string lastCommand = commandDetails[index]->commandType;
	commandDetails.pop_back();
	return lastCommand;
}

int Logic::getDeadlineSize(void) {
	return storage.retrieveDeadlineSize();
}

int Logic::getNormalSize(void) {
	return storage.retrieveNormalSize();
}

int Logic::getFloatingSize(void) {
	return storage.retrieveFloatingSize();
}

std::vector<int> Logic::getColourIndex(void){
	return storage.retrieveColourIndex();
}

std::string Logic::receiveCommand(std::string userInput) {
	std::string displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

std::string Logic::executeLogicCore(std::string userInput) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	if (parser.isRecurring(userInput)) {
		return executeRecurringTask(userInput, index);
	}
	else {
		parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
		TASK_TYPE taskType = determineSpecificTaskType(index);
		return executeTask(taskType, index);
	}
}

std::string Logic::executeRecurringTask(std::string userInput, int index) {
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStartRecur, commandDetails[index]->dateEndRecur, commandDetails[index]->timeStartRecur, commandDetails[index]->timeEndRecur);
	return storage.addRecurringTask(commandDetails[index]->task, commandDetails[index]->dateStartRecur, commandDetails[index]->dateEndRecur, commandDetails[index]->timeStartRecur, commandDetails[index]->timeEndRecur);
}

std::string Logic::executeTask(TASK_TYPE taskType, int index) {
	std::string displayMessageToUI;
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
	case ERASE:
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
	case DISPLAY:
		displayMessageToUI = " ";
		break;
	case CD:
		storage.changeDirectory(commandDetails[index]->task);
		break;
	case INVALID:
		displayMessageToUI = STRING_INVALID;
		break;
	} 
	assert(!displayMessageToUI.empty());
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int index) {
	date dateNull(not_a_date_time);
	if(commandDetails[index]->commandType==STRING_ADD) {
		if((commandDetails[index]->timeEnd==not_a_date_time) && (commandDetails[index]->dateEnd==dateNull)) {
			return FLOATING;
		}
		else if((commandDetails[index]->timeStart==not_a_date_time) && (commandDetails[index]->dateStart==dateNull)) {
			return DEADLINE;
		}
		else {
			return NORMAL;
		}
	}
	else if(commandDetails[index]->commandType==STRING_DELETE) {
		return ERASE;
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
	else if (commandDetails[index]->commandType == STRING_DISPLAY) {
		return DISPLAY;
	}
	else if (commandDetails[index]->commandType == STRING_CD) {
		return CD;
	}
	else return INVALID;
}

bool Logic::lastCommandIsSearch(void) {
	int index = commandDetails.size()-2;
	return ((index>=0) && (commandDetails[index]->commandType == STRING_SEARCH));
}

Storage* Logic::getStorage() {
	return &storage;
}