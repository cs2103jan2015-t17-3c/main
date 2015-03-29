#include "UI.h"

const string UI::MESSAGE_DEFAULT = "Commands available:add, delete, edit, search, undo\nEnter Command:";
const string UI::MESSAGE_DEFAULT_CHECK = "Commands available:completed, reschedule\nEnter Command:";
const string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";
const string UI::MESSAGE_TOPTEN = "Below is the list of top ten items in your scheduler\n\n";
const string UI::MESSAGE_FLOAT = "Below are the tasks without specific date or time\n";
const string UI::MESSAGE_SEARCH = "Below is the search result\n";
const string UI::MESSAGE_CHECK = "Have you completed the following task(s)?\n";
const string UI::MESSAGE_CHECK_ADD = "Before add, have you completed the following task(s)?\n";
const string UI::MESSAGE_CHECK_DELETE = "Before delete, have you completed the following task(s)?\n";
const string UI::MESSAGE_CHECK_SEARCH = "Before search, have you completed the following task(s)?\n";
const string UI::MESSAGE_CHECK_EDIT = "Before edit, have you completed the following task(s)?\n";
const string UI::MESSAGE_CHECK_ARCHIVE = "Before showing archive, have you completed the following task(s)?\n";

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
		cout << "Today: "<<today << endl << endl;
		assert(command != "");
		if (logic.getCommandType(command) == "search"){
			cout << MESSAGE_SEARCH << endl;
			displayMessage = logic.displaySearchResults(command);
			printVectorToUser(displayMessage);
		} else{
			cout << MESSAGE_TOPTEN;
			displayMessage = logic.displayTopTen();
			printVectorToUser(displayMessage);
			cout << MESSAGE_FLOAT;
			displayMessage = logic.displayFloatingTask();
			printVectorToUser(displayMessage);
		}
		//The above is the top segment
		printToUser(message);
		//The above is the middle segment
		cout << endl << endl << MESSAGE_DEFAULT;
		getline(cin, command);
		//The above is the bottom segment
		std::system("CLS");
		checkOverdue(command);
		//continue with the execution if the command is not check
		if (command != "check"){
			message = logic.receiveCommand(command);
		}
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

bool UI::checkOverdue(string command){
	Logic logic;
	string message=" ";
	if (logic.displayOverdue().empty()){
		return false;
	}
	while (!logic.displayOverdue().empty()){
		string commandType=logic.getCommandType(command);
		if (commandType == "add"){
			printToUser(MESSAGE_CHECK_ADD);
		}else if (commandType == "delete"){
			printToUser(MESSAGE_CHECK_DELETE);
		}else if (commandType == "edit"){
			printToUser(MESSAGE_CHECK_EDIT);
		}else if (commandType == "search"){
			printToUser(MESSAGE_CHECK_SEARCH);
		}else if (commandType == "archive"){
			printToUser(MESSAGE_CHECK_ARCHIVE);
		}else{
			printToUser(MESSAGE_CHECK);
		}
		printVectorToUser(logic.displayOverdue());
		//top
		printToUser(message);
		//middle
		cout << endl;
		printToUser(MESSAGE_DEFAULT_CHECK);
		//bottom
		getline(cin, command);
		message = logic.receiveCommand(command);
	}
	std::system("CLS");
	return true;
}