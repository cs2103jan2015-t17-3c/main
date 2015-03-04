
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
	//parser.processCommand(userInput, &commandDetails.commandType, &commandDetails.task, &commandDetails.timeStart ,&commandDetails.timeEnd, &commandDetails.itemToDelete);
	//string displayMessage = storage.processCommand(commandDetails.commandType, commandDetails.task, commandDetails.timeStart ,commandDetails.timeEnd, commandDetails.itemToDelete); 
	//return displayMessage;
}
