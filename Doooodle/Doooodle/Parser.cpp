#include "Parser.h"

const string Parser::DELIMITERS = " ";
const int Parser::NO_OF_TIME_INDICATORS = 6;
const string Parser::TIME_INDICATORS[NO_OF_TIME_INDICATORS] = { " from "," by "," at "," on "," in ", " to "};

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
	size_t positionA = 0;
	size_t positionB = 0;
	string task;
	positionB = input.find_first_of(DELIMITERS);
	task = input.substr(positionA, positionB - positionA);

	return task;
}
string Parser::getUserTask(string input){
	size_t positionA=0;
	size_t positionB=0;
	string task;
	positionA = input.find_first_of(DELIMITERS);
	positionA++;
	for (int i = 0; i < NO_OF_TIME_INDICATORS; i++){
		positionB = input.find(TIME_INDICATORS[i], positionA + 1);
		if (positionB != string::npos){
			break;
		}
	}
	task = input.substr(positionA, positionB - positionA);

	return task;
}


string Parser::getStartDetail(string input){
	size_t positionA = 0;
	size_t positionB = 0;
	string task;
	for (int i = 0; i < NO_OF_TIME_INDICATORS; i++){
		positionA = input.find(TIME_INDICATORS[i]);
		if (positionA != string::npos && TIME_INDICATORS[i]!=" by "){
			positionA = input.find(DELIMITERS, positionA + 1);
			positionA++;
			positionB = input.find(DELIMITERS, positionA);
			break;
		}
	}
	if (positionB==0){
		task = "";
	}
	else{
		task = input.substr(positionA, positionB - positionA);
	}
	return task;
}

string Parser::getEndDetail(string input){
	size_t positionA = 0;
	size_t positionB = 0;
	string task;
	for (int i = 0; i < NO_OF_TIME_INDICATORS; i++){
		positionA = input.find(TIME_INDICATORS[i]);
		if (positionA != string::npos && TIME_INDICATORS[i] != " from "){
			positionA = input.find(DELIMITERS, positionA + 1);
			positionA++;
			positionB = input.find(DELIMITERS, positionA);
			break;
		}
	}
	if (positionB == 0){
		task = "";
	}
	else{
		task = input.substr(positionA, positionB - positionA);
	}
	return task;
}