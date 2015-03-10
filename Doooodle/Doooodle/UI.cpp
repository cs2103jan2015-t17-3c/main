#include "UI.h"

const string UI::MESSAGE_ADD = "added to calendar successfully";
const string UI::MESSAGE_DEFAULT = "Enter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";
const string UI::MESSAGE_TOPFIVE = "Below is the list of top five items in your scheduler for now\n";

UI::UI(void) {
}
UI::~UI(void) {
}
void UI::readMessage(){
	string command;
	string message;
	string displayMessage;

	cout << MESSAGE_WELCOME;
	while (true){
		cout << MESSAGE_TOPFIVE;
		displayMessage = logic.displayTopFive();
		printToUser(displayMessage);	
		cout << MESSAGE_DEFAULT;
		getline(cin, command);
		cout << endl;
		message = logic.receiveCommand(command);
		printToUser(message);
	}
}

void UI::printToUser(string message){
	cout << message;
}
