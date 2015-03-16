
#include "Logic.h"

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

vector<string> Logic::displayTopFive(void) {
	return storage.retrieveTopFive();
}

string Logic::receiveCommand(string userInput) {
	string displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

string Logic::executeLogicCore(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart, commandDetails[indexToUpdate]->timeEnd);
	TASK_TYPE taskType = determineSpecificTaskType(indexToUpdate);
	return executeTask(taskType, indexToUpdate);
}

string Logic::executeTask(TASK_TYPE taskType, int indexToUpdate) {
	string displayMessageToUI;
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
		displayMessageToUI = "";
		break;
	case INVALID:
		displayMessageToUI = "ERROR!";
		break;
	} 
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	boost::gregorian::date d2(boost::date_time::not_a_date_time);
	if(commandDetails[indexToUpdate]->commandType=="add") {
		if((commandDetails[indexToUpdate]->timeEnd==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateEnd==d2)) {
			return FLOATING;
		}
		else if((commandDetails[indexToUpdate]->timeStart==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateStart==d2)) {
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