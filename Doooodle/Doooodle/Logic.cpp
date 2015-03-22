
#include "Logic.h"

const string Logic::STRING_ADD = "add";
const string Logic::STRING_DELETE = "delete";
const string Logic::STRING_EDIT = "edit";
const string Logic::STRING_EXIT = "exit";
const string Logic::STRING_INVALID = "ERROR!";
const string Logic::STRING_REDO = "redo";
const string Logic::STRING_SEARCH = "search";
const string Logic::STRING_UNDO = "undo";

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
	assert(commandDetails[indexToUpdate]->commandType==STRING_SEARCH);
	return searchTask.loadTask(commandDetails[indexToUpdate]->task, storage);
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
		displayMessageToUI = normTask.loadTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart ,commandDetails[indexToUpdate]->timeEnd, storage);
		break;
	case DEADLINE:
		displayMessageToUI = deadlineTask.loadTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeEnd, storage);
		break;
	case FLOATING:
		displayMessageToUI = floatingTask.loadTask(commandDetails[indexToUpdate]->task, storage);
		break;
	case DELETE:
		if (lastCommandIsSearch()) {
			displayMessageToUI = deleteSearchTask.loadTask(atoi((commandDetails[indexToUpdate]->task).c_str()), storage);
		}
		else{
			displayMessageToUI = deleteTask.loadTask(atoi((commandDetails[indexToUpdate]->task).c_str()), storage);
		}
		break;
	case SEARCH:
		break;
	case EXIT:
		exit(0);
		break;
	case UNDO:
		displayMessageToUI = undoTask.loadTask(commandDetails, commandDetailsForRedo, storage);
		storage.sortStorage();
		storage.writeToFile();
		break;
	case REDO:
		displayMessageToUI = redoTask.loadTask(commandDetailsForRedo, storage);
		storage.sortStorage();
		storage.writeToFile();	
		break;
	case EDIT:
		//displayMessageToUI = " ";
		break;
	case INVALID:
		displayMessageToUI = STRING_INVALID;
		break;
	} 
	assert(displayMessageToUI!=" ");
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	if(commandDetails[indexToUpdate]->commandType==STRING_ADD) {
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
	else if(commandDetails[indexToUpdate]->commandType==STRING_DELETE) {
		return DELETE;
	}
	else if(commandDetails[indexToUpdate]->commandType==STRING_SEARCH) {
		return SEARCH;
	}
	else if(commandDetails[indexToUpdate]->commandType==STRING_EXIT) {
		return EXIT;
	}
	else if(commandDetails[indexToUpdate]->commandType==STRING_UNDO) {
		return UNDO;
	}
	else if(commandDetails[indexToUpdate]->commandType==STRING_EDIT) {
		return EDIT;
	}
	else if(commandDetails[indexToUpdate]->commandType==STRING_REDO) {
		return REDO;
	}

	else return INVALID;
}

bool Logic::lastCommandIsSearch(void) {
	int index = commandDetails.size()-2;
	return (commandDetails[index]->commandType==STRING_SEARCH);
}