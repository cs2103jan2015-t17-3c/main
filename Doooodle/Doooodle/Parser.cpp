#include "Parser.h"

const int Parser::POSITION_COMMAND_TYPE = 0;
const string Parser::DELIMITERS = " ";
const int Parser::NO_OF_START_TIME_INDICATORS = 1;
const int Parser::NO_OF_END_TIME_INDICATORS = 5;
const int Parser :: NO_OF_TIME_IDENTIFIERS = 20;
const string Parser::START_TIME_INDICATORS[NO_OF_START_TIME_INDICATORS] = { " from "};
const string Parser::END_TIME_INDICATORS[NO_OF_END_TIME_INDICATORS] = { " by ", " at ", " on ", " in ", " to " };
const string Parser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                  "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
                                                                  "Today","today","Tomorrow", "tomorrow" };
Parser::Parser(){

}
Parser::~Parser(){

}

void Parser::processCommand(string input, string& commandType, string& userTask, boost::gregorian::date& startDate, boost::gregorian::date& endDate, 
	boost::posix_time::ptime& startTime, boost::posix_time::ptime& endTime){
	boost::gregorian::date d1(boost::date_time::not_a_date_time);
	boost::posix_time::ptime d2(boost::date_time::not_a_date_time);
	int pos;
	tokenizeInput(input);    //tokenize string by white space
	commandType = getCommandType(input);
	userTask = getUserTask(input);
	startDate = getStartDate(pos);
	endDate = getEndDate(pos);
	startTime = getStartTime(pos);
	endTime = getEndTime(pos);
	if (startDate == endDate && startTime == endTime){
		startDate = d1;
		startTime = d2;
	}
	if (startDate == d1&&startTime != d2){
		assignToday(startDate);
	}
	if (endDate == d1&&endTime != d2){
		assignToday(endDate);
	}
	if (endDate != d1&&endTime == d2){
		ptime t(endDate, boost::posix_time::hours(23)+boost::posix_time::minutes(59));
		endTime = t;
	}
	return;
}

void Parser::tokenizeInput(string input){
	string buf; 
	tokens.clear();
	stringstream ss(input); // Insert the string into a stream
	while (ss >> buf)
		tokens.push_back(buf);
}

string Parser::getCommandType(string input){
	string task;
	task = tokens[POSITION_COMMAND_TYPE];
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


boost::gregorian::date Parser::getStartDate(int& num){
	DateParser dateparser;
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	string task;
	string str;
	for (int i = 0; i < tokens.size(); i++){
		if (dateparser.isDate(tokens[i])){
			num = i;
			return dateparser.standardiseDate(tokens[i]);
		}
	}
	return d;
}

boost::gregorian::date Parser::getEndDate(int& num){
	DateParser dateparser;
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	string task;
	for (int i = tokens.size()-1; i > 0; i--){
		if (dateparser.isDate(tokens[i])){
			num = i;
			return dateparser.standardiseDate(tokens[i]);
		}
	}
	return d;
}
boost::posix_time::ptime Parser::getStartTime(int& num){
	TimeParser timeparser;
	boost::posix_time::ptime d(boost::date_time::not_a_date_time);
	string task;
	for (int i = 0; i < tokens.size(); i++){
		if (timeparser.isTime(tokens[i])){
			num = i;
			return timeparser.standardTime(tokens[i]);	
		}
	}
		return d;
}

boost::posix_time::ptime Parser::getEndTime(int& num){
	TimeParser timeparser;
	boost::posix_time::ptime d(boost::date_time::not_a_date_time);
	string task;
	for (int i = tokens.size()-1; i > 0; i--){
		if (timeparser.isTime(tokens[i])){
			return timeparser.standardTime(tokens[i]);
			num = i;
		}
	}
	return d;
}

size_t Parser::intToPos(int num,string input){
	size_t positionA=0;
	for (int i = 0; i < num; i++){
		positionA = input.find(" ", positionA+1);
	}
	return positionA;
}

size_t Parser::getStartOfUserTask(string input){
	size_t pos;
	pos=input.find_first_of(DELIMITERS);
	pos++;
	return pos;
}

size_t Parser::getEndOfUserTask(string input){
	size_t pos;
	int num;
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
	getStartDate(num);
	pos = intToPos(num, input);
	pos++;

	return pos;
}

void Parser::assignToday(boost::gregorian::date& d){
	boost::gregorian::date today(day_clock::local_day());
	d = today;
	return;
}