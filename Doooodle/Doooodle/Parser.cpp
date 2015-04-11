#include "Parser.h"

const date Parser::DATE_INVALID(max_date_time);
const ptime Parser::TIME_INVALID(max_date_time);
const int Parser::DEFAULT_SIZE=1000;
const int Parser::DEFAULT_RECURRENCE=-1;
const int Parser::DEFAULT_INTERVAL=1;
const int Parser::RECURRING_POSITION = 1;
const int Parser::DEFAULT_TASK_TYPE_POSITION = 0;
const int Parser::FIRST_PARAMETER = 0;
const int Parser::SECOND_PARAMETER = 1;
const int Parser::THIRD_PARAMETER = 2;
const int Parser::NO_PARAMETER_FREQUENCY = 1;
const int Parser::NO_PARAMETER_FREQUENCY_BOUNDARY = 2;
const int Parser::NO_PARAMETER_ALL = 3;
const int Parser::NO_SEARCH_MONTH = 2;
const date Parser::DATE_EMPTY;
const ptime Parser::TIME_EMPTY;
const int Parser::POSITION_COMMAND_TYPE = 0;
const int Parser::POSITION_USER_TASK = 1;
const std::string Parser::DEADLINE_INDICATOR = "by";
const std::string Parser::DELIMITERS = " ";
const std::string Parser::RECURRING_INDENTIFIER = " ;";
const std::string Parser::RIGID_INDENTIFIER = ",*";
const std::string Parser::ALL_DELIMITER = " ,*";
const int Parser::NO_OF_START_TIME_INDICATORS = 1;
const int Parser::NO_OF_END_TIME_INDICATORS = 5;
const int Parser::NO_OF_NORMAL_IDENTIFIERS = 5;
const int Parser::NO_OF_DEADLINE_IDENTIFIERS = 4;
const int Parser::NO_OF_FLOAT_IDENTIFIERS = 8;
const int Parser::NO_OF_ARCHIVE_IDENTIFIERS = 2;
const std::string Parser::DISPLAY_COMMAND="display";
const std::string Parser::SEARCH_COMMAND="search";
const std::string Parser::DELETE_COMMAND="delete";
const std::string Parser::EDIT_COMMAND="edit";
const std::string Parser::INVALID_DATE = "Invalid Date";
const std::string Parser::EMPTY = "Empty Task";
const std::string Parser::DEFAULT_YEAR_SEARCH="1900";
const std::string Parser::DEFAULT_DAY_SEARCH = "01";
const std::string Parser::NORMAL_IDENTIFIERS[NO_OF_NORMAL_IDENTIFIERS] = { "normal", "N", "norm", "Norm", "Normal"};
const std::string Parser::DEADLINE_IDENTIFIERS[NO_OF_DEADLINE_IDENTIFIERS] = {"floating","Float", "float", "Floating" };
const std::string Parser::FLOAT_IDENTIFIERS[NO_OF_FLOAT_IDENTIFIERS] = { "deadline", "Deadline", "d", "D", "dead", "Dead", "dateline", "Dateline" };
const std::string Parser::ARCHIVE_IDENTIFIERS[NO_OF_ARCHIVE_IDENTIFIERS] = { "archive", "Archive" };
const std::string Parser::START_TIME_INDICATORS[NO_OF_START_TIME_INDICATORS] = { " from "};
const std::string Parser::END_TIME_INDICATORS[NO_OF_END_TIME_INDICATORS] = { " by ", " at ", " on ", " in ", " to " };

Parser::Parser(){

}
Parser::~Parser(){

}

bool Parser::isRecurring(std::string input){
	if (input.find(RECURRING_INDENTIFIER[RECURRING_POSITION]) != std::string::npos){
		return true;
	}
	return false;
}

bool Parser::isRigid(std::string input){
	for (int i = 0; i < RIGID_INDENTIFIER.length();i++)
		if (input.find(RIGID_INDENTIFIER[i]) != std::string::npos){
		return true;
	}
	return false;
}

void Parser::processCommand(std::string input, std::string& commandType, std::string& userTask, std::vector<date>& vecStartDate, std::vector<date>& vecEndDate, std::vector<ptime>& vecStartTime, std::vector<ptime>& vecEndTime){
	std::string frequency;
	int recurrence = DEFAULT_RECURRENCE;
	int interval = DEFAULT_INTERVAL;
	int dummyIndexReference;
	date finishDate;
	date startDate;
	date endDate;
	ptime startTime;
	ptime endTime;

	processCommand(separateRecurringFront(input), commandType, userTask, startDate, endDate, startTime, endTime, dummyIndexReference);
	if (startDate == DATE_EMPTY && endDate == DATE_EMPTY && startTime == TIME_EMPTY && endTime == TIME_EMPTY){
		commandType = INVALID_DATE;
		return;
	}
	getRecurringParameter(separateRecurringBack(input), frequency, interval, recurrence, finishDate);
	vecStartDate.push_back(startDate);
	vecEndDate.push_back(endDate);
	vecStartTime.push_back(startTime);
	vecEndTime.push_back(endTime);
	dateparser.completeRecurring(frequency, vecStartDate, vecEndDate, vecStartTime, vecEndTime,recurrence,interval,finishDate);
	
	return;
}

void Parser::processCommand(std::string input, std::string& commandType, std::string& userTask, date& startDate, date& endDate, 
	ptime& startTime, ptime& endTime, int& indexReference){
	int pos;
	if (isRigid(input)){
		tokenizeInput(input, RIGID_INDENTIFIER);
		commandType = tokens[POSITION_COMMAND_TYPE];
		userTask = tokens[POSITION_USER_TASK];
		eraseUserTask(input, tokens[POSITION_USER_TASK]);
	}
	else{
		tokenizeInput(input, DELIMITERS);    //tokenize string by white space
		commandType = getCommandType(input);
		if (commandType == SEARCH_COMMAND){
			monthParsingForSearch(input);
		}
		userTask = getUserTask(input);
	}
		indexReference = getIndexReference(input);
		startDate = getStartDate(pos);
		endDate = getEndDate(pos);
		startTime = getStartTime(pos);
		endTime = getEndTime(pos);
		if (commandType == DISPLAY_COMMAND){
		if (!userTaskParsing(userTask)){
			commandType = EMPTY;
		}
	}
	//date or time is identifed but not correct date format
	if (startDate == DATE_INVALID || endDate == DATE_INVALID || startTime == TIME_INVALID || endTime == TIME_INVALID){
		commandType = INVALID_DATE;
	}
	//if start date time and end date time are the same, only keep the end date time
	if (startDate == endDate && startTime == endTime){
		startDate = DATE_EMPTY;
		startTime = TIME_EMPTY;
	}
	//if only have time, the default date is today
	if (startDate == DATE_EMPTY && startTime != TIME_EMPTY && getCommandType(input) != EDIT_COMMAND){
		assignToday(startDate);
	}
	//if only have time, the default date is today
	if (endDate == DATE_EMPTY && endTime != TIME_EMPTY && getCommandType(input) != EDIT_COMMAND){
		assignToday(endDate);
	}
	//if only have date and it is a deadline task, a default time of 2359 will be assigned
	if (endDate != DATE_EMPTY && endTime == TIME_EMPTY && isDeadline(input)){
		ptime t(endDate, hours(23)+minutes(59)+seconds(59));
		endTime = t;
	}
	if ((endDate < startDate && startDate != DATE_EMPTY) || (endDate == startDate && endTime < startTime && startDate != DATE_EMPTY && startTime!=TIME_EMPTY)){
		commandType = INVALID_DATE;
	}

	return;
}

void Parser::tokenizeInput(std::string input,std::string delimiters){
	tokens.clear();
	char str[DEFAULT_SIZE] = " ";
	for (int i = 0; i < input.size(); i++){
		str[i] = input[i];
	}
	char * pch;
	pch = strtok(str, delimiters.c_str());
	while (pch != NULL)
	{
		tokens.push_back(pch);
		pch = strtok(NULL, delimiters.c_str());
	}
}

std::string Parser::getCommandType(std::string input){
	std::string task;
	if (input == "") {
		task = DELIMITERS;
	}
	else {
		task = tokens[POSITION_COMMAND_TYPE];
	}
	return task;
}

int Parser::getIndexReference(std::string input){
	if (getCommandType(input) == DELETE_COMMAND || getCommandType(input) == EDIT_COMMAND || getCommandType(input) == "complete"){
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
	size_t position = 0; 
	if (tokens.size() > num){
		position = input.find(tokens[num][0], position);
		return position - 1;
	}
	else if (tokens.size() == num && tokens.size() != 0){
		return input.find(tokens[num - 1]) + tokens[num - 1].length();
	}
	else{
		return 0;
	}
}

size_t Parser::getStartOfUserTask(std::string input){
	size_t pos;
	pos=input.find_first_of(DELIMITERS);
	pos++;
	//if the command is delete or edit, the start of the user task is one position after the index
	if (getCommandType(input) == DELETE_COMMAND || getCommandType(input) == EDIT_COMMAND){
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

	position++;
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
		if (tokens[i] ==DEADLINE_INDICATOR){
			return true;
		}
	}
	return false;
}

bool Parser::userTaskParsing(std::string& input){
	bool check = true;
	for (int i = 0; i < NO_OF_NORMAL_IDENTIFIERS; i++){
		if (input == NORMAL_IDENTIFIERS[i]){
			input = NORMAL_IDENTIFIERS[DEFAULT_TASK_TYPE_POSITION];
			return check;
		}
	}
	for (int i = 0; i < NO_OF_DEADLINE_IDENTIFIERS; i++){
		if (input == DEADLINE_IDENTIFIERS[i]){
			input = DEADLINE_IDENTIFIERS[DEFAULT_TASK_TYPE_POSITION];
			return check;
		}
	}
	for (int i = 0; i < NO_OF_FLOAT_IDENTIFIERS; i++){
		if (input == FLOAT_IDENTIFIERS[i]){
			input = FLOAT_IDENTIFIERS[DEFAULT_TASK_TYPE_POSITION];
			return check;
		}
	}
	for (int i = 0; i < NO_OF_ARCHIVE_IDENTIFIERS; i++){
		if (input == ARCHIVE_IDENTIFIERS[i]){
			input = ARCHIVE_IDENTIFIERS[DEFAULT_TASK_TYPE_POSITION];
			return check;
		}
	}
	return false;
}

void Parser::getRecurringParameter(std::string input,std::string& frequency, int& interval, int& recurrence, date& finish){
	std::vector<std::string> items;
	items=recurringTokenizer(input);
	if (items.size() >= NO_PARAMETER_FREQUENCY){
		frequencyParsing(items[FIRST_PARAMETER], interval, frequency);
	}
	if (items.size() >= NO_PARAMETER_FREQUENCY_BOUNDARY){
		if (dateparser.isDate(items[SECOND_PARAMETER])){
			finish = dateparser.standardiseDate(items[SECOND_PARAMETER]);
		}else{
			recurrence = atoi(items[SECOND_PARAMETER].c_str());
		}
	}
	if (items.size() >= NO_PARAMETER_ALL){
		if (dateparser.isDate(items[THIRD_PARAMETER])){
			finish = dateparser.standardiseDate(items[THIRD_PARAMETER]);
		}else{
			recurrence = atoi(items[THIRD_PARAMETER].c_str());
		}
	}
	return;
}

std::vector<std::string> Parser::recurringTokenizer(std::string input){
	std::vector<std::string> recurringTokens;
	char str[DEFAULT_SIZE] = " ";
	for (int i = 0; i < input.size(); i++){
		str[i] = input[i];
	}
	char * pch;
	pch = strtok(str, RECURRING_INDENTIFIER.c_str());
	while (pch != NULL)
	{
		recurringTokens.push_back(pch);
		pch = strtok(NULL, RECURRING_INDENTIFIER.c_str());
	}
	return recurringTokens;
}

void Parser::monthParsingForSearch(std::string& input){
	size_t pos;
	size_t nextpos;
	std::ostringstream oss;
	oss << DEFAULT_YEAR_SEARCH;
	if (tokens.size() == NO_SEARCH_MONTH){
		for (int i = 0; i < tokens.size(); i++){
			if (dateparser.monthToNum(tokens[i]) <= Dec && dateparser.monthToNum(tokens[i]) >= Jan){
				if (dateparser.monthToNum(tokens[i]) >= Oct){
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

std::string Parser::separateRecurringFront(std::string input){
	size_t pos;
	pos = input.find(RECURRING_INDENTIFIER[RECURRING_POSITION]);
	return input.substr(0, pos);
}

std::string Parser::separateRecurringBack(std::string input){
	size_t pos;
	pos = input.find(RECURRING_INDENTIFIER[RECURRING_POSITION]);
	return input.substr(pos, input.length()-pos);
}

void Parser::eraseUserTask(std::string input, std::string userTask){
	size_t pos;
	pos=input.find(userTask);
	input.erase(pos, userTask.length());
	tokenizeInput(input, ALL_DELIMITER);
	return;
}
