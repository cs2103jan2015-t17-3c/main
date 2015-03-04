#include "UI.h"

const string UI::MESSAGE_ADD = "added to calendar successfully";
const string UI::MESSAGE_DEFAULT = "Enter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";

UI::UI(void) {
}
UI::~UI(void) {
}
void UI::readMessage(){
	string command;
	string message;
	cout << MESSAGE_WELCOME;
	while (true){
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
