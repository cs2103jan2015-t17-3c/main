
#include "Logic.h"

char Logic::buffer[300];
const string Logic::MESSAGE_ADD = "add";
const string Logic::MESSAGE_DELETE = "delete";
const string Logic::MESSAGE_EDIT = "edit";
const string Logic::MESSAGE_EXIT = "exit";
const string Logic::MESSAGE_INVALID = "ERROR!";
const string Logic::MESSAGE_REDO = "redo";
const string Logic::MESSAGE_SEARCH = "search";
const string Logic::MESSAGE_UNDO = "undo";

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

vector<string> Logic::displayTopFive(void) {
	vector<string> topFiveToDisplay = storage.retrieveTopFive();
	assert(topFiveToDisplay.size()<=5);
	return topFiveToDisplay; 
}

vector<string> Logic::displaySearchResults(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	assert(commandDetails[indexToUpdate]->commandType==MESSAGE_SEARCH);
	return searchTask.loadSearchTask(commandDetails[indexToUpdate]->task, storage);
}


string Logic::receiveCommand(string userInput) {
	string displayMessage = executeLogicCore(userInput);
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

string Logic::executeLogicCore(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	TASK_TYPE taskType = determineSpecificTaskType(indexToUpdate);
	return executeTask(taskType, indexToUpdate);
}

string Logic::executeTask(TASK_TYPE taskType, int indexToUpdate) {
	string displayMessageToUI=" ";
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
		if (lastCommandIsSearch()) {
			displayMessageToUI = deleteSearchTask.loadDeleteTask(atoi((commandDetails[indexToUpdate]->task).c_str()), storage);
		}
		else{
			displayMessageToUI = deleteTask.loadDeleteTask(atoi((commandDetails[indexToUpdate]->task).c_str()), storage);
		}
		break;
	case SEARCH:
		displayMessageToUI = MESSAGE_INVALID;
		break;
	case EXIT:
		exit(0);
		break;
	case UNDO:
		displayMessageToUI = undoTask.loadUndoTask(commandDetails, storage);
		storage.sortStorage();
		storage.writeToFile();
		break;
	case EDIT:
		//displayMessageToUI = " ";
		break;
	case INVALID:
		displayMessageToUI = MESSAGE_INVALID;
		break;
	} 
	assert(displayMessageToUI!=" ");
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	if(commandDetails[indexToUpdate]->commandType==MESSAGE_ADD) {
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
	else if(commandDetails[indexToUpdate]->commandType==MESSAGE_DELETE) {
		return DELETE;
	}
	else if(commandDetails[indexToUpdate]->commandType==MESSAGE_SEARCH) {
		return SEARCH;
	}
	else if(commandDetails[indexToUpdate]->commandType==MESSAGE_EXIT) {
		return EXIT;
	}
	else if(commandDetails[indexToUpdate]->commandType==MESSAGE_UNDO) {
		return UNDO;
	}
	else if(commandDetails[indexToUpdate]->commandType==MESSAGE_EDIT) {
		return EDIT;
	}
	else return INVALID;
}

bool Logic::lastCommandIsSearch(void) {
	int index = commandDetails.size()-2;
	cout << commandDetails[index]->commandType << "         " << MESSAGE_SEARCH << endl;
	return (commandDetails[index]->commandType==MESSAGE_SEARCH);
}