
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
	int intToPass;
	switch(taskType) {
	case NORMAL:
		displayMessageToUI = normTask.loadNormalTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateStart ,commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeStart ,commandDetails[indexToUpdate]->timeEnd, storage);
		storage.writeToFile();
		break;
	case DEADLINE:
		displayMessageToUI = deadlineTask.loadDeadlineTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->dateEnd, commandDetails[indexToUpdate]->timeEnd, storage);
		storage.writeToFile();
		break;
	case FLOATING:
		displayMessageToUI = floatingTask.loadFloatingTask(commandDetails[indexToUpdate]->task, storage);
		storage.writeToFile();
		break;
	case DELETE:
		intToPass = atoi((commandDetails[indexToUpdate]->task).c_str());
		displayMessageToUI = storage.deleteTask(intToPass);
		storage.writeToFile();
		break;
	case SEARCH:
		displayMessageToUI = storage.searchTask(commandDetails[indexToUpdate]->task);
		storage.writeToFile();
		break;
	case EXIT:
		exit(0);
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
}