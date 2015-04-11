
#include "Logic.h"

const std::string Logic::STRING_ADD = "add";
const std::string Logic::STRING_ARCHIVE = "archive";
const std::string Logic::STRING_CD = "cd";
const std::string Logic::STRING_COMPLETE = "complete";
const std::string Logic::STRING_DISPLAY = "display";
const std::string Logic::STRING_DELETE = "delete";
const std::string Logic::STRING_EDIT = "edit";
const std::string Logic::STRING_EXIT = "exit";
const std::string Logic::STRING_HELP = "help";
const std::string Logic::STRING_INVALID = "ERROR!";
const std::string Logic::STRING_NIL = " ";
const std::string Logic::STRING_SEARCH = "search";
const std::string Logic::STRING_UNDO = "undo";

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

//facade to shield from logic execution
std::string Logic::receiveCommand(std::string userInput) {
	std::string displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

//Start of getter functions 
std::vector<std::string> Logic::displayTopList(void) {
	std::vector<std::string> listToDisplay = storage.retrieveTopList();
	return listToDisplay; 
}

std::vector<std::string> Logic::displayFloatingTask(void) {
	std::vector<std::string> floatingTask = storage.retrieveFloatingTask();
	return floatingTask; 
}

std::vector<std::string> Logic::displaySearchResults(std::string userInput) {
	int index = createDynamicNewCommandDetails();
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	assert(commandDetails[index]->commandType==STRING_SEARCH);
	return searchTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateEnd, commandDetails[index]->timeEnd, storage);
}

std::vector<std::string> Logic::displayCategoricalTask(std::string userInput, std::string& taskType) {
	int index = createDynamicNewCommandDetails();
	parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
	taskType = commandDetails[index]->task;
	return storage.retrieveCategoricalTask(taskType);
}

std::string Logic::getCommandType(std::string userInput) {
	int index = createDynamicNewCommandDetails();
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

Storage* Logic::getStorage() {
	return &storage;
}
//end of getter functions


std::string Logic::executeLogicCore(std::string userInput) {
	int index = createDynamicNewCommandDetails();
	std::string displayMessage = determineParserCase(userInput, index);
	return displayMessage;
}

//index refers to the last element in commandDetail vector
int Logic::createDynamicNewCommandDetails(void) {
	int index = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	return index;
}

//Parser public function works differently based on parameter passed. 1 for Recurring and 1 for every other commands
std::string Logic::determineParserCase(std::string userInput, int index) {
	if (parser.isRecurring(userInput)) {
		parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStartRecur, commandDetails[index]->dateEndRecur, commandDetails[index]->timeStartRecur, commandDetails[index]->timeEndRecur);
		return executeRecurringTask(userInput, index);
	}
	else {
		parser.processCommand(userInput, commandDetails[index]->commandType, commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, commandDetails[index]->indexReference);
		TASK_TYPE taskType = determineSpecificTaskType(index);
		return executeTask(taskType, index);
	}
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int index) {
	date dateNull(not_a_date_time);
	//if there are no dates or time, it is a floating task
	//if there is ONE date and/or time, it is a deadline task
	//else it is a normal task
	if (commandDetails[index]->commandType == STRING_ADD) {
		if ((commandDetails[index]->timeEnd == not_a_date_time) && (commandDetails[index]->dateEnd == dateNull)) {
			return FLOATING;
		}
		else if ((commandDetails[index]->timeStart == not_a_date_time) && (commandDetails[index]->dateStart == dateNull)) {
			return DEADLINE;
		}
		else {
			return NORMAL;
		}
	}
	else if (commandDetails[index]->commandType == STRING_DELETE) {
		return ERASE;
	}
	else if (commandDetails[index]->commandType == STRING_SEARCH) {
		return SEARCH;
	}
	else if (commandDetails[index]->commandType == STRING_EXIT) {
		return EXIT;
	}
	else if (commandDetails[index]->commandType == STRING_UNDO) {
		return UNDO;
	}
	else if (commandDetails[index]->commandType == STRING_EDIT) {
		return EDIT;
	}
	else if (commandDetails[index]->commandType == STRING_COMPLETE) {
		return COMPLETE;
	}
	else if (commandDetails[index]->commandType == STRING_DISPLAY) {
		return DISPLAY;
	}
	else if (commandDetails[index]->commandType == STRING_CD) {
		return CD;
	}
	else if (commandDetails[index]->commandType == STRING_HELP) {
		return HELP;
	}
	else return INVALID;
}

bool Logic::lastCommandIsSearch(void) {
	int index = commandDetails.size() - 2; //-2 to ignore the most recent command
	return ((index >= 0) && (commandDetails[index]->commandType == STRING_SEARCH));
}

std::string Logic::executeTask(TASK_TYPE taskType, int index) {
	std::string displayMessageToUI;
	switch (taskType) {
		//loadTask method goes through Interface Class ITask for command when last command is not "search",
		//delete, edit, and complete have to take into account if last user command is "search" and hence calls a different method
		//string_NIL are returned for functions that will not return a message, such as when the user types "display normal"
	case NORMAL:
		displayMessageToUI = normTask.loadTask(commandDetails[index]->task, commandDetails[index]->dateStart, commandDetails[index]->dateEnd, commandDetails[index]->timeStart, commandDetails[index]->timeEnd, storage);
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
		displayMessageToUI = STRING_NIL;
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
	case COMPLETE:
		if (lastCommandIsSearch()) {
			displayMessageToUI = overdueTask.completeSearchTask(commandDetails[index]->indexReference, storage);
		}
		else{
			displayMessageToUI = overdueTask.completeTask(commandDetails[index]->indexReference, storage);
		}
		break;
	case DISPLAY:
		displayMessageToUI = STRING_NIL;
		break;
	case CD:
		displayMessageToUI = storage.changeDirectory(commandDetails[index]->task);
		break;
	case HELP:
		displayMessageToUI = STRING_NIL;
		break;
	case INVALID:
		displayMessageToUI = STRING_INVALID;
		break;
	}
	assert(!displayMessageToUI.empty());
	return displayMessageToUI;
}

std::string Logic::executeRecurringTask(std::string userInput, int index) {
	return storage.addRecurringTask(commandDetails[index]->task, commandDetails[index]->dateStartRecur, commandDetails[index]->dateEndRecur, commandDetails[index]->timeStartRecur, commandDetails[index]->timeEndRecur);
}