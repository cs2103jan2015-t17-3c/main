#include "Parser.h"

const string Parser::DELIMITERS = " ";
const string Parser::TIME_INDICATORS[10] = { "from","by" };
const int Parser::NO_OF_TIME_INDICATORS = 2;
Parser::Parser(){

}
Parser::~Parser(){

}

void Parser::processCommand(string input,string& commandType,string& userTask,
	string& startDetail, string& endDetail){
	commandType = getCommandType(input);
	userTask = getUserTask(input);
	startDetail = getStartDetail(input);
	endDetail = getEndDetail(input);

	return;
}

string Parser::getCommandType(string input){
	size_t positionA=0;
	size_t positionB=0;
	string command;
	positionA = input.find_first_of(DELIMITERS);
	for (int i = 0; i < NO_OF_TIME_INDICATORS; i++){
		positionB = input.find(TIME_INDICATORS[i], positionA + 1);
		if (positionB != string::npos){
			break;
		}
	}
	command = input.substr(positionA, positionB - positionA);

	return command;
}

string Parser::getUserTask(string input){
	size_t positionA = 0;
	size_t positionB = 0;
	string task;
	positionB = input.find_first_of(DELIMITERS);
	task = input.substr(positionA, positionB - positionA);

	return task;
}
string Parser::getStartDetail(string input){
	return "12:00 pm";
}
string Parser::getEndDetail(string input){
	return "2:00 pm";
}
