#include "Parser.h"

const string Parser::DELIMITERS = " ";

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

string getUserTask(string);
string getStartDetail(string);
string getEndDetail(string);
