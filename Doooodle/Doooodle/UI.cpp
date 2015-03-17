#include "UI.h"

const string UI::MESSAGE_ADD = "added to calendar successfully";
const string UI::MESSAGE_DEFAULT = "Enter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";
const string UI::MESSAGE_TOPFIVE = "Below is the list of top five items in your scheduler for now\n\n";

UI::UI(void) {
}
UI::~UI(void) {
}

void UI::readMessage(){
	string command;
	string message = " ";
	vector<string> displayMessage;

	while (true){
		cout << MESSAGE_WELCOME << endl;
		cout << MESSAGE_TOPFIVE;
		if (logic.isSearch()){
			displayMessage = logic.displaySearchResults();
		}
		else{
			displayMessage = logic.displayTopFive();
		}
		printVectorToUser(displayMessage);
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		//The above is the top segment
		printToUser(message);
		//The above is the middle segment
		cout << endl << endl << MESSAGE_DEFAULT;
		getline(cin, command);
		//The above is the bottom segment
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		message = logic.receiveCommand(command);
	}
}


void UI::printToUser(string message){
	cout << message << endl;
}

void UI::printVectorToUser(vector<string> vec){
	for (int i = 0; i<vec.size(); i++){
		printToUser(vec[i]);
	}
}
