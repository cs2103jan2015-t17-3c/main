#include "Parser.h"

const int Parser::POSITION_COMMAND_TYPE = 0;
const string Parser::DELIMITERS = " ";
const int Parser::NO_OF_START_TIME_INDICATORS = 1;
const int Parser::NO_OF_END_TIME_INDICATORS = 5;
const int Parser :: NO_OF_TIME_IDENTIFIERS = 18;
const string Parser::INVALID_DATE = "Invalid Date";
const string Parser::EMPTY = "Empty Task";
const string Parser::START_TIME_INDICATORS[NO_OF_START_TIME_INDICATORS] = { " from "};
const string Parser::END_TIME_INDICATORS[NO_OF_END_TIME_INDICATORS] = { " by ", " at ", " on ", " in ", " to " };
const string Parser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { " Monday", " Tuesday", " Wednesday", " Thursday", " Friday", " Saturday", " Sunday",
                                                                  " monday", " tuesday", " wednesday", " thursday", " friday", " saturday", " sunday",
                                                                  " Today"," today"," Tomorrow", " tomorrow" };
Parser::Parser(){

}
Parser::~Parser(){

}

void Parser::processCommand(string input, string& commandType, string& userTask, boost::gregorian::date& startDate, boost::gregorian::date& endDate, 
	boost::posix_time::ptime& startTime, boost::posix_time::ptime& endTime, int& indexReference){
	boost::gregorian::date d1(boost::date_time::not_a_date_time);
	boost::gregorian::date dmax(boost::date_time::max_date_time);
	boost::posix_time::ptime d2(boost::date_time::not_a_date_time);
	boost::posix_time::ptime pmax(boost::posix_time::max_date_time);
	int pos;
	tokenizeInput(input);    //tokenize string by white space
	
	commandType = getCommandType(input);
	indexReference = getIndexReference(input);
	userTask = getUserTask(input);
	startDate = getStartDate(pos);
	endDate = getEndDate(pos);
	startTime = getStartTime(pos);
	endTime = getEndTime(pos);

	if (commandType == "display"){
		userTaskParsing(userTask);
	}

	if (userTask == EMPTY){
		commandType = EMPTY;
	}
	//date or time is identifed but not correct date format
	if (startDate == dmax || endDate == dmax || startTime==pmax || endTime==pmax){
		commandType = INVALID_DATE;
	}
	//if start date time and end date time are the same, only keep the end date time
	if (startDate == endDate && startTime == endTime){
		startDate = d1;
		startTime = d2;
	}
	//if only have time, the default date is today
	if (startDate == d1 && startTime != d2 && getCommandType(input)!="edit"){
		assignToday(startDate);
	}
	//if only have time, the default date is today
	if (endDate == d1 && endTime != d2 && getCommandType(input)!="edit"){
		assignToday(endDate);
	}
	//if only have date and it is a deadlin task, a default time of 2359 will be assigned
	if (endDate != d1 && endTime == d2 && isDeadline(input)){
		ptime t(endDate, boost::posix_time::hours(23)+boost::posix_time::minutes(59)+boost::posix_time::seconds(59));
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

int Parser::getIndexReference(string input){
	if (getCommandType(input) == "delete" || getCommandType(input) == "edit"){
		for (int i = 0; i < tokens.size(); i++){
			if (isdigit(tokens[i][0])){
				return atoi(tokens[i].c_str());
			}
		}
	}
	return -1;
}

string Parser::getUserTask(string input){
	size_t positionA=0;
	size_t positionB=0;
	string task;
	positionA = getStartOfUserTask(input);
	positionB = getEndOfUserTask(input);
	if (positionA <= positionB){
		return EMPTY;
	}
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
			if (i == 0){
				return dateparser.standardiseDate(tokens[i], tokens[i], tokens[i + 1],num,i);
			}else if (i == tokens.size() - 1){
				return dateparser.standardiseDate(tokens[i - 1], tokens[i], tokens[i],num,i);
			}else{
				return dateparser.standardiseDate(tokens[i - 1], tokens[i], tokens[i + 1],num,i);
			}
		}
	}
	num = tokens.size();
	return d;
}

boost::gregorian::date Parser::getEndDate(int& num){
	DateParser dateparser;
	boost::gregorian::date d(boost::date_time::not_a_date_time);
	string task;
	for (int i = tokens.size()-1; i > 0; i--){
		if (dateparser.isDate(tokens[i])){
			if (i == 0){
				return dateparser.standardiseDate(tokens[i], tokens[i], tokens[i + 1],num,i);
			}else if (i == tokens.size() - 1){
				return dateparser.standardiseDate(tokens[i - 1], tokens[i], tokens[i],num,i);
			}else{
				return dateparser.standardiseDate(tokens[i - 1], tokens[i], tokens[i + 1],num,i);
			}
		}
	}
	num = tokens.size();
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
	num = tokens.size();
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
	num = tokens.size();
	return d;
}

size_t Parser::intToPos(int num,string input){
	size_t position=0;
	for (int i = 0; i < num; i++){
		position = input.find(" ", position+1);
	}
	return position;
}

size_t Parser::getStartOfUserTask(string input){
	size_t pos;
	pos=input.find_first_of(DELIMITERS);
	pos++;
	if (getCommandType(input) == "delete" || getCommandType(input) == "edit"){
		pos = input.find_first_of(DELIMITERS,pos);
		pos++;
	}
	return pos;
}

size_t Parser::getEndOfUserTask(string input){
	size_t pos=string::npos;
	size_t position=string::npos;
	int num;
	//check for start time indicators
	for (int i = 0; i < NO_OF_START_TIME_INDICATORS; i++){
		pos = input.find(START_TIME_INDICATORS[i]);
		if (pos != string::npos){
			break;
		}
	}
	position = min(position, pos);

	//check for time indentidiers
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++){
		pos = input.find(TIME_IDENTIFIERS[i]);
		if (pos != string::npos){
			break;
		}
	}
	position = min(position, pos);

	//check for end time indicators
	for (int i = 0; i < NO_OF_END_TIME_INDICATORS; i++){
		pos = input.find(END_TIME_INDICATORS[i]);
		if (pos != string::npos){
			break;
		}
	}
	position = min(position, pos);

	//check for date
	getStartDate(num);
	pos = intToPos(num, input);
	position = min(position, pos);

	//check for time;
	getStartTime(num);
	pos = intToPos(num, input);
	position = min(position, pos);
	
	position++;
	//return the smallest position of a time or date which is the end position of user task
	return position;
}

void Parser::assignToday(boost::gregorian::date& d){
	boost::gregorian::date today(day_clock::local_day());
	d = today;
	return;
}

bool Parser::isDeadline(string input){
	for (int i = 0; i < tokens.size(); i++){
		if (tokens[i]=="by"){
			return true;
		}
	}
	return false;
}

void Parser::userTaskParsing(string& input){
	if (input == "Normal" || input == "N" || input == "norm" || input == "Norm"){
		input = "normal";
	}else if (input == "Float" || input == "float" || input == "Floating"){
		input = "floating";
	}else if (input == "Deadline" || input == "d" || input == "D" || input == "dead" || input == "Dead" || input == "dateline" || input == "Dateline"){
		input = "deadline";
	}else if (input == "Archive"){
		input = "archive";
	}
}