#include "UI.h"

const string UI::MESSAGE_DEFAULT = "Commands available:add, delete, edit, search\nEnter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************                                     ";
const string UI::MESSAGE_TOPTEN = "Below is the list of top ten items in your scheduler for now\n\n";
const string UI::MESSAGE_FLOAT = "Below is the tasks without specific date or time\n";

UI::UI(void) {
}
UI::~UI(void) {
}

void UI::readMessage(){
	string command = "Nothing";
	string message = " ";
	date today(day_clock::local_day());
	vector<string> displayMessage;
	cout << MESSAGE_WELCOME;
	cout << today << endl;

	while (true){
		//assertion added by cindy
		assert(command != "");
		if (logic.isSearch(command)){
			displayMessage = logic.displaySearchResults(command);
			printVectorToUser(displayMessage);
		}else{
			cout << MESSAGE_TOPTEN;
			displayMessage = logic.displayTopTen();
			printVectorToUser(displayMessage);
			cout << MESSAGE_FLOAT;
			displayMessage = logic.displayFloatingTask();
			printVectorToUser(displayMessage);
		}
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
