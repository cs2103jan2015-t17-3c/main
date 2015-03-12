
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
		displayMessageToUI = storage.deleteTask(atoi((commandDetails[indexToUpdate]->task).c_str));
		break;
	case SEARCH:
		displayMessageToUI = storage.searchTask(commandDetails[indexToUpdate]->task);
		break;
	case EXIT:
		storage.writeToFile("Doooodle.txt");
		break;
	} 
	return displayMessageToUI;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	if(commandDetails[indexToUpdate]->commandType=="add") {
		if((commandDetails[indexToUpdate]->timeEnd==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateEnd==boost::gregorian::not_a_date_time)) {
			return FLOATING;
		}
		else if((commandDetails[indexToUpdate]->timeStart==boost::posix_time::not_a_date_time) && (commandDetails[indexToUpdate]->dateStart==boost::gregorian::not_a_date_time)) {
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