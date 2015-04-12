//@author A0115016X -unused
#include "UI.h"

const std::string UI::MESSAGE_DEFAULT = "Commands available:add, delete, edit, search, undo, complete, display\nEnter Command:";
const std::string UI::MESSAGE_DEFAULT_CHECK = "Commands available:completed, reschedule\nEnter Command:";
const std::string UI::MESSAGE_WELCOME = "*************************\n\
*        Doooodle       *\n*************************\n";
const std::string UI::MESSAGE_TOPTEN = "Below is the list of upcoming events in your calendar";
const std::string UI::MESSAGE_FLOAT = "Below are the floating tasks";
const std::string UI::MESSAGE_SEARCH = "Below is the search result\n";
const std::string UI::MESSAGE_CATEGORICAL_TASK1 = "Below is the whole list of the ";
const std::string UI::MESSAGE_CATEGORICAL_TASK2 = " tasks\n";
const std::string UI::MESSAGE_CHECK = "Have you completed the following task(s)?\n";
const std::string UI::MESSAGE_CHECK_ADD = "Before add, have you completed the following task(s)?\n";
const std::string UI::MESSAGE_CHECK_DELETE = "Before delete, have you completed the following task(s)?\n";
const std::string UI::MESSAGE_CHECK_SEARCH = "Before search, have you completed the following task(s)?\n";
const std::string UI::MESSAGE_CHECK_EDIT = "Before edit, have you completed the following task(s)?\n";
const std::string UI::MESSAGE_CHECK_ARCHIVE = "Before showing archive, have you completed the following task(s)?\n";

UI::UI(void) {
}
UI::~UI(void) {
}

void UI::readMessage(){
	std::string command = "Nothing";
	std::string message = " ";
	date today(day_clock::local_day());
	std::vector<std::string> displayMessage;
	std::string cat;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 245);
	std::cout << MESSAGE_WELCOME;
	SetConsoleTextAttribute(hConsole, 240);

	while (true){
		std::cout << "Today: "<<today << std::endl << std::endl;
		assert(command != "");
		if (logic.getCommandType(command) == "search"){
			SetConsoleTextAttribute(hConsole, 249);
			printToUser(MESSAGE_SEARCH);
			displayMessage = logic.displaySearchResults(command);
			SetConsoleTextAttribute(hConsole, 248);
			printVectorToUser(displayMessage);
		} else if (logic.getCommandType(command)=="display"){
			displayMessage = logic.displayCategoricalTask(command,cat);
			SetConsoleTextAttribute(hConsole, 249);
			std::cout<<MESSAGE_CATEGORICAL_TASK1;
			std::cout << cat;
			std::cout<<MESSAGE_CATEGORICAL_TASK2<<std::endl;
			SetConsoleTextAttribute(hConsole, 248);
			printVectorToUser(displayMessage);
		} else {
			SetConsoleTextAttribute(hConsole, 249);
			std::cout << MESSAGE_TOPTEN;
			displayMessage = logic.displayTopTask();
			SetConsoleTextAttribute(hConsole, 252);
			std::cout << "  [" << logic.getDeadlineSize() << "]"; 
			SetConsoleTextAttribute(hConsole, 242);
			std::cout << " [" << logic.getNormalSize() << ']' << std::endl;
			SetConsoleTextAttribute(hConsole, 248);
			printVectorToUser(displayMessage);
			std::cout << std::endl;
			SetConsoleTextAttribute(hConsole, 249);
			std::cout<<MESSAGE_FLOAT;
			SetConsoleTextAttribute(hConsole, 251);
			displayMessage = logic.displayFloatingTask();
			std::cout << "  [" << logic.getFloatingSize() << ']' << std::endl;
			SetConsoleTextAttribute(hConsole, 248);
			printVectorToUser(displayMessage);
		}
		std::cout << std::endl;
		//The above is the top segment
		SetConsoleTextAttribute(hConsole, 225);
		printToUser(message);
		//The above is the middle segment
		SetConsoleTextAttribute(hConsole, 240);
		std::cout << MESSAGE_DEFAULT;
		SetConsoleTextAttribute(hConsole, 244);
		std::getline(std::cin, command);
		//The above is the bottom segment
		std::system("CLS");
		
		//continue with the execution if the command is not check
		if (command != "check"){
			message = logic.receiveCommand(command);
		}
//		checkOverdue(command);
	}
}


void UI::printToUser(std::string message){
	std::cout << message << std::endl;
}

void UI::printVectorToUser(std::vector<std::string> vec){
	for (int i = 0; i<vec.size(); i++){
		printToUser(vec[i]);
	}
}
/*
bool UI::checkOverdue(std::string command){
	std::string message=" ";
	if (logic.displayOverdue().empty()){
		return false;
	}
	while (!logic.displayOverdue().empty()){
		std::string commandType=logic.getCommandType(command);
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
		std::cout << std::endl;
		std::cout<<MESSAGE_DEFAULT_CHECK;
		//bottom
		std::getline(std::cin, command);
		message = logic.receiveCommand(command);
	}
	std::system("CLS");
	return true;
}
*/