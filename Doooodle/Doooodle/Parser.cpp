#include "Parser.h"

const string Parser::DELIMITERS = " ";

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
	positionB = input.find_first_of(DELIMITERS);
	command = input.substr(positionA, positionB - positionA);

	return command;
}

string Parser::getUserTask(string input){
	return "Task";
}
string Parser::getStartDetail(string input){
	return "12:00 pm";
}
string Parser::getEndDetail(string input){
	return "2:00 pm";
}
