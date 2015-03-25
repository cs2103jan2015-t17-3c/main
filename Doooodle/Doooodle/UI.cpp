#include "UI.h"

const string UI::MESSAGE_DEFAULT = "Commands available:add, delete, edit, search\nEnter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";
const string UI::MESSAGE_TOPTEN = "Below is the list of top ten items in your scheduler for now\n\n";
const string UI::MESSAGE_FLOAT = "Below is the tasks without specific date or time\n";
const string UI::MESSAGE_SEARCH = "Below is the search result\n";
const int UI::NUMBER_OF_TOTAL_LINES = 12;
const int UI::NUMBER_OF_SEARCH_LINES = 27;
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

	while (true){
		//assertion added by cindy
		cout << "Today: "<<today << endl << endl;
		assert(command != "");
		if (logic.isSearch(command)){
			cout << MESSAGE_SEARCH << endl;
			displayMessage = logic.displaySearchResults(command);
			printVectorToUser(displayMessage);
			printSearchLine(displayMessage.size());
		}else{
			cout << MESSAGE_TOPTEN;
			displayMessage = logic.displayTopTen();
			printVectorToUser(displayMessage);
			printEmptyLine(displayMessage.size());
			cout << MESSAGE_FLOAT;
			displayMessage = logic.displayFloatingTask();
			printVectorToUser(displayMessage);
			printEmptyLine(displayMessage.size());
		}
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

void UI::printEmptyLine(int num){
	for (int i = num; i < NUMBER_OF_TOTAL_LINES; i++){
		cout << endl;
	}
}

void UI::printSearchLine(int num){
	for (int i = num; i < NUMBER_OF_SEARCH_LINES; i++){
		cout << endl;
	}
}