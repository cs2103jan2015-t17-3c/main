
#include "Logic.h"

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

vector<string> Logic::displayTopFive(void) {
	vector<string> topFiveToDisplay = storage.retrieveTopFive();
	assert(topFiveToDisplay.size()==5);
	return topFiveToDisplay; 
}

vector<string> Logic::displaySearchResult(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	assert(commandDetails[indexToUpdate]->commandType=="search");
	return searchTask.loadSearchTask(commandDetails[indexToUpdate]->task, storage);
}


vector<string> Logic::receiveCommand(string userInput) {
	vector<string> displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

bool Logic::isSearch(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	TASK_TYPE taskType = determineSpecificTaskType(indexToUpdate);
	if (taskType == SEARCH) {
		commandDetails.pop_back();
		return true;
	}
	else {
		commandDetails.pop_back();
		return false;
	}
}

vector<string> Logic::executeLogicCore(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	TASK_TYPE taskType = determineSpecificTaskType(indexToUpdate);
	return executeTask(taskType, indexToUpdate);
}

vector<string> Logic::executeTask(TASK_TYPE taskType, int indexToUpdate) {
	vector<string> displayMessageToUI;
	vector<string> displayInvalidMessage;
	displayInvalidMessage.push_back("ERROR!");
	switch(taskType) {
	case NORMAL:
		displayMessageToUI = normTask.loadNormalTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart ,commandDetails[indexToUpdate]->timeEnd, storage);
		break;
	case DEADLINE:
		displayMessageToUI = deadlineTask.loadDeadlineTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeEnd, storage);
		break;
	case FLOATING:
		displayMessageToUI = floatingTask.loadFloatingTask(commandDetails[indexToUpdate]->task, storage);
		break;
	case DELETE:
		displayMessageToUI = deleteTask.loadDeleteTask(atoi((commandDetails[indexToUpdate]->task).c_str()), storage);
		break;
	case SEARCH:
		displayMessageToUI = searchTask.loadSearchTask(commandDetails[indexToUpdate]->task, storage);
		break;
	case EXIT:
		exit(0);
		break;
	case UNDO:
		displayMessageToUI = undoTask.loadUndoTask(commandDetails, storage);
		storage.writeToFile;
		break;
	case EDIT:
		//displayMessageToUI = " ";
		break;
	case INVALID:
		displayMessageToUI = displayInvalidMessage;
		break;
	} 
	assert(displayMessageToUI.size()!=0);
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	if(commandDetails[indexToUpdate]->commandType=="add") {
		if((commandDetails[indexToUpdate]->timeEnd==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateEnd==d)) {
			return FLOATING;
		}
		else if((commandDetails[indexToUpdate]->timeStart==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateStart==d)) {
			return DEADLINE;
		}
		else {
			return NORMAL;
		}
	}
	else if(commandDetails[indexToUpdate]->commandType=="delete") {
		return DELETE;
	}
	else if(commandDetails[indexToUpdate]->commandType=="search") {
		return SEARCH;
	}
	else if(commandDetails[indexToUpdate]->commandType=="exit") {
		return EXIT;
	}
	else if(commandDetails[indexToUpdate]->commandType=="undo") {
		return UNDO;
	}
	else if(commandDetails[indexToUpdate]->commandType=="edit") {
		return EDIT;
	}
	else return INVALID;
}