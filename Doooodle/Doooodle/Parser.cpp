#include "Parser.h"

const date Parser::DATE_INVALID(not_a_date_time);
const ptime Parser::TIME_INVALID(not_a_date_time);
const int Parser::POSITION_COMMAND_TYPE = 0;
const std::string Parser::DELIMITERS = " ";
const std::string Parser::RECURRING_INDENTIFIER = " ;";
const int Parser::NO_OF_START_TIME_INDICATORS = 1;
const int Parser::NO_OF_END_TIME_INDICATORS = 5;
const std::string Parser::INVALID_DATE = "Invalid Date";
const std::string Parser::EMPTY = "Empty Task";
const std::string Parser::DEFAULT_YEAR_SEARCH="1900";
const std::string Parser::DEFAULT_DAY_SEARCH = "01";
const std::string Parser::START_TIME_INDICATORS[NO_OF_START_TIME_INDICATORS] = { " from "};
const std::string Parser::END_TIME_INDICATORS[NO_OF_END_TIME_INDICATORS] = { " by ", " at ", " on ", " in ", " to " };

Parser::Parser(){

}
Parser::~Parser(){

}

bool Parser::isRecurring(std::string input){
	if (input.find(RECURRING_INDENTIFIER) != std::string::npos){
		return true;
	}
	return false;
}

bool Parser::isRigid(std::string input){
	if (input.find('*') != std::string::npos){
		return true;
	}
	return false;
}

void Parser::processCommand(std::string input, std::string& commandType, std::string& userTask, std::vector<date>& vecStartDate, std::vector<date>& vecEndDate, std::vector<ptime>& vecStartTime, std::vector<ptime>& vecEndTime){
	std::string frequency;
	int recurrence=-1;
	int interval = 1;
	int dummyIndexReference;
	date finishDate(not_a_date_time);
	date startDate(not_a_date_time);
	date endDate(not_a_date_time);
	ptime startTime(not_a_date_time);
	ptime endTime(not_a_date_time);
	processCommand(input, commandType, userTask, startDate, endDate, startTime, endTime, dummyIndexReference);
	if (startDate == DATE_INVALID && endDate == DATE_INVALID && startTime == TIME_INVALID && endTime == TIME_INVALID){
		commandType = INVALID_DATE;
		return;
	}
	getRecurringParameter(input, frequency, interval,recurrence, finishDate);
	vecStartDate.push_back(startDate);
	vecEndDate.push_back(endDate);
	vecStartTime.push_back(startTime);
	vecEndTime.push_back(endTime);
	dateparser.completeRecurring(frequency, vecStartDate, vecEndDate, vecStartTime, vecEndTime,recurrence,interval,finishDate);
	
	return;
}

void Parser::processCommand(std::string input, std::string& commandType, std::string& userTask, date& startDate, date& endDate, 
	ptime& startTime, ptime& endTime, int& indexReference){
	date d1(not_a_date_time);
	date dmax(max_date_time);
	ptime d2(not_a_date_time);
	ptime pmax(max_date_time);
	int pos;
	if (isRigid(input)){
		rigidTokenizer(input);
		commandType = tokens[0];
		userTask = tokens[1];
		startDate = dateparser.standardiseDate(tokens[2]);
		endDate = dateparser.standardiseDate(tokens[4]);
		startTime = timeparser.standardTime(tokens[3]);
		endTime = timeparser.standardTime(tokens[5]);
	}else{
		tokenizeInput(input);    //tokenize string by white space
		commandType = getCommandType(input);
		if (commandType == "search"){
			monthParsingForSearch(input);
		}
		indexReference = getIndexReference(input);
		userTask = getUserTask(input);
		startDate = getStartDate(pos);
		endDate = getEndDate(pos);
		startTime = getStartTime(pos);
		endTime = getEndTime(pos);
	}
	if (commandType == "display"){
		if (!userTaskParsing(userTask)){
			commandType = EMPTY;
		}
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
		ptime t(endDate, hours(23)+minutes(59)+seconds(59));
		endTime = t;
	}
	return;
}

void Parser::tokenizeInput(std::string input){
	std::string buf; 
	tokens.clear();
	std::stringstream ss(input); // Insert the string into a stream
	while (ss >> buf)
		tokens.push_back(buf);
}

void Parser::rigidTokenizer(std::string input){
	tokens.clear();
	char str[1000]=" ";
	for (int i = 0; i < input.size(); i++){
		str[i] = input[i];
	}
	char * pch;
	pch = strtok(str, "*");
	while (pch != NULL)
	{
		tokens.push_back(pch);
		pch = strtok(NULL, "*");
	}
}

std::string Parser::getCommandType(std::string input){
	std::string task;
	if (input == "") {
		task = " ";
	}
	else {
		task = tokens[POSITION_COMMAND_TYPE];
	}
	return task;
}

int Parser::getIndexReference(std::string input){
	if (getCommandType(input) == "delete" || getCommandType(input) == "edit"|| getCommandType(input)=="complete"){
		for (int i = 0; i < tokens.size(); i++){
			if (isdigit(tokens[i][0])){
				return atoi(tokens[i].c_str());
			}
		}
	}
	return -1;
}

std::string Parser::getUserTask(std::string input){
	size_t positionA=0;
	size_t positionB=0;
	std::string task;
	positionA = getStartOfUserTask(input);
	positionB = getEndOfUserTask(input);
	task = input.substr(positionA, positionB - positionA);
	return task;
}


date Parser::getStartDate(int& num){
	date d(not_a_date_time);
	std::string task;
	std::string str;
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

date Parser::getEndDate(int& num){
	date d(not_a_date_time);
	std::string task;
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

ptime Parser::getStartTime(int& num){
	ptime d(not_a_date_time);
	std::string task;
	for (int i = 0; i < tokens.size(); i++){
		if (timeparser.isTime(tokens[i])){
			num = i;
			return timeparser.standardTime(tokens[i]);	
		}
	}
	num = tokens.size();
	return d;
}

ptime Parser::getEndTime(int& num){
	ptime d(not_a_date_time);
	std::string task;
	for (int i = tokens.size()-1; i > 0; i--){
		if (timeparser.isTime(tokens[i])){
			return timeparser.standardTime(tokens[i]);
			num = i;
		}
	}
	num = tokens.size();
	return d;
}

size_t Parser::intToPos(int num,std::string input){
	size_t position=0;
	for (int i = 0; i < num; i++){
		position = input.find(" ", position+1);
	}
	return position;
}

size_t Parser::getStartOfUserTask(std::string input){
	size_t pos;
	pos=input.find_first_of(DELIMITERS);
	pos++;
	if (getCommandType(input) == "delete" || getCommandType(input) == "edit"){
		pos = input.find_first_of(DELIMITERS,pos);
		pos++;
	}
	return pos;
}

size_t Parser::getEndOfUserTask(std::string input){
	size_t pos=std::string::npos;
	size_t position=std::string::npos;
	int num;
	//check for start time indicators
	for (int i = 0; i < NO_OF_START_TIME_INDICATORS; i++){
		pos = input.find(START_TIME_INDICATORS[i]);
		if (pos != std::string::npos){
			break;
		}
	}
	position = std::min(position, pos);

	//check for end time indicators
	for (int i = 0; i < NO_OF_END_TIME_INDICATORS; i++){
		pos = input.find(END_TIME_INDICATORS[i]);
		if (pos != std::string::npos){
			break;
		}
	}
	position = std::min(position, pos);

	//check for date
	getStartDate(num);
	pos = intToPos(num, input);
	position = std::min(position, pos);

	//check for time;
	getStartTime(num);
	pos = intToPos(num, input);
	position = std::min(position, pos);
	if (position == std::string::npos){
		position = input.length();
	}
	else{
		position++;
	}
	//return the smallest position of a time or date which is the end position of user task
	return position;
}

void Parser::assignToday(date& d){
	date today(day_clock::local_day());
	d = today;
	return;
}

bool Parser::isDeadline(std::string input){
	for (int i = 0; i < tokens.size(); i++){
		if (tokens[i]=="by"){
			return true;
		}
	}
	return false;
}

bool Parser::userTaskParsing(std::string& input){
	bool check = true;
	if (input == "Normal" || input == "N" || input == "norm" || input == "Norm" || input == "normal"){
		input = "normal";
	}else if (input == "floating" || input == "Float" || input == "float" || input == "Floating"){
		input = "floating";
	}else if (input=="deadline" || input == "Deadline" || input == "d" || input == "D" || input == "dead" || input == "Dead" || input == "dateline" || input == "Dateline"){
		input = "deadline";
	}else if (input == "Archive" || input=="archive"){
		input = "archive";
	}else {
		check=false;
	}
	return check;
}

void Parser::getRecurringParameter(std::string input,std::string& frequency, int& interval, int& recurrence, date& finish){
	std::vector<std::string> items;
	items=recurringTokenizer(input);
	if (items.size() >= 2){
		frequencyParsing(items[1], interval, frequency);
	}
	if (items.size() >= 3){
		if (dateparser.isDate(items[2])){
			finish = dateparser.standardiseDate(items[2]);
		}else{
			recurrence = atoi(items[2].c_str());
		}
	}
	if (items.size() >= 4){
		if (dateparser.isDate(items[3])){
			finish = dateparser.standardiseDate(items[3]);
		}else{
			recurrence = atoi(items[3].c_str());
		}
	}
	return;
}

std::vector<std::string> Parser::recurringTokenizer(std::string input){
	std::vector<std::string> recurringTokens;
	char str[1000] = " ";
	for (int i = 0; i < input.size(); i++){
		str[i] = input[i];
	}
	char * pch;
	pch = strtok(str, ";");
	while (pch != NULL)
	{
		recurringTokens.push_back(pch);
		pch = strtok(NULL, ";");
	}
	return recurringTokens;
}

void Parser::monthParsingForSearch(std::string& input){
	size_t pos;
	size_t nextpos;
	std::ostringstream oss;
	oss << DEFAULT_YEAR_SEARCH;
	if (tokens.size() == 2){
		for (int i = 0; i < tokens.size(); i++){
			if (dateparser.monthToNum(tokens[i]) <= 12 && dateparser.monthToNum(tokens[i]) >= 1){
				if (dateparser.monthToNum(tokens[i]) >= 10){
					oss << std::to_string(dateparser.monthToNum(tokens[i])) << DEFAULT_DAY_SEARCH;
				}
				else{
					oss << std::to_string(0) << std::to_string(dateparser.monthToNum(tokens[i])) << DEFAULT_DAY_SEARCH;
				}
				tokens[i] = oss.str();
				break;
			}
		}
	}
	return;
}

void Parser::frequencyParsing(std::string input,int& interval,std::string& frequency){
	for (int i = 0; i < input.length(); i++){
		if (isdigit(input[i])){
			frequency = input.substr(0, i);
			interval = atoi(input.substr(i, input.length() - i).c_str());
			return;
		}
	}
	frequency = input;
	return;
}