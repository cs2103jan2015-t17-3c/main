#include "Parser.h"

const string Parser::DELIMITERS = " ";
const int Parser::NO_OF_START_TIME_INDICATORS = 1;
const int Parser::NO_OF_END_TIME_INDICATORS = 5;
const int Parser :: NO_OF_TIME_IDENTIFIERS = 20;
const string Parser::START_TIME_INDICATORS[NO_OF_START_TIME_INDICATORS] = { " from "};
const string Parser::END_TIME_INDICATORS[NO_OF_END_TIME_INDICATORS] = { " by ", " at ", " on ", " in ", " to " };
const string Parser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                  "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
                                                                  "Tomorrow", "tomorrow" };
Parser::Parser(){

}
Parser::~Parser(){

}

void Parser::processCommand(string input, string& commandType, string& userTask, boost::gregorian::date& startDate, boost::gregorian::date& endDate, 
	boost::posix_time::ptime& startTime, boost::posix_time::ptime& endTime){
	commandType = getCommandType(input);
	userTask = getUserTask(input);
	startDate = getStartDate(input);
	endDate = getEndDate(input);
	startTime = getStartTime(input);
	endTime = getEndTime(input);

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
	positionA = getStartOfUserTask(input);
	positionB = getEndOfUserTask(input);
	task = input.substr(positionA, positionB - positionA);

	return task;
}


boost::gregorian::date Parser::getStartDate(string input){
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

boost::gregorian::date& Parser::getEndDate(string input){
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

size_t Parser::getStartOfUserTask(string input){
	size_t pos;
	pos=input.find_first_of(DELIMITERS);
	pos++;
	return pos;
}

size_t Parser::getEndOfUserTask(string input){
	size_t pos;
	for (int i = 0; i < NO_OF_START_TIME_INDICATORS; i++){
		pos = input.find(START_TIME_INDICATORS[i]);
		if (pos != string::npos){
			return pos;
		}
	}
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++){
		pos = input.find(TIME_IDENTIFIERS[i]);
		if (pos != string::npos){
			return pos;
		}
	}

}