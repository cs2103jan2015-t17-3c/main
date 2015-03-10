
#include "Logic.h"

Logic::Logic(void) {
}

Logic::~Logic(void) {
}

string Logic::receiveCommand(string userInput) {
	string displayMessage = executeLogicCore(userInput);
	return displayMessage;
}

string Logic::executeLogicCore(string userInput) {
	int indexToUpdate = commandDetails.size();
	commandDetails.push_back(new CommandDetails());
	parser.processCommand(userInput, commandDetails[indexToUpdate]->commandType, commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->timeStart ,commandDetails[indexToUpdate]->timeEnd);
	TASK_TYPE taskType = determineSpecificTaskType(indexToUpdate);
	string displayMessage;
	switch(taskType) {
	case NORMAL:
		normTask.loadNormalTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->timeStart ,commandDetails[indexToUpdate]->timeEnd, storage);
		break;
	case DEADLINE:
		displayMessage = storage.addDueTask(commandDetails[indexToUpdate]->task, commandDetails[indexToUpdate]->timeEnd);
		break;
	case FLOATING:
		displayMessage = storage.addFloatTask(commandDetails[indexToUpdate]->task);
		break;
	} 
	return displayMessage;
}

Logic::TASK_TYPE Logic::determineSpecificTaskType(int indexToUpdate) {
	if(commandDetails[indexToUpdate]->timeEnd=="") {
		return FLOATING;
	}
	else if(commandDetails[indexToUpdate]->timeStart=="") {
		return DEADLINE;
	}
	else {
		return NORMAL;
	}
}