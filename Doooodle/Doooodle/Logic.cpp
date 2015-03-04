
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
	//parser.processCommand(userInput, &commandDetails[indexToUpdate].commandType, &commandDetails[indexToUpdate].task, &commandDetails[indexToUpdate].timeStart ,&commandDetails[indexToUpdate].timeEnd, &commandDetails[indexToUpdate].itemToDelete);
	//string displayMessage = storage.processCommand(commandDetails[indexToUpdate].commandType, commandDetails[indexToUpdate].task, commandDetails[indexToUpdate].timeStart ,commandDetails[indexToUpdate].timeEnd, commandDetails[indexToUpdate].itemToDelete); 
	//return displayMessage;
}
