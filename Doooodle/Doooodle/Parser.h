//@author A0114321B
#ifndef PARSER_H_
#define PARSER_H_

#include "DateParser.h"
#include "TimeParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/date_time.hpp>
#include <ostream>

using namespace boost::gregorian;
using namespace boost::posix_time;

class Parser {

private:
	DateParser dateparser;
	TimeParser timeparser;
	std::vector<std::string> tokens;
	static const int ERROR_MESSAGE;
	static const int FIRST_PARAMETER;
	static const int SECOND_PARAMETER;
	static const int THIRD_PARAMETER;
	static const int NO_PARAMETER_FREQUENCY;
	static const int NO_PARAMETER_FREQUENCY_BOUNDARY;
	static const int NO_PARAMETER_ALL;
	static const int NO_SEARCH_MONTH;
	static const int DEFAULT_SIZE;
	static const int DEFAULT_RECURRENCE;
	static const int DEFAULT_INTERVAL;
	static const int DEFAULT_TASK_TYPE_POSITION;
	static const int RECURRING_POSITION;
	static const int DEADLINE_HOURS;
	static const int DEADLINE_MINUTES;
	static const int DEADLINE_SECONDS;
	static const date DATE_INVALID;
	static const date DATE_EMPTY;
	static const ptime TIME_INVALID;
	static const ptime TIME_EMPTY;
	static const int POSITION_COMMAND_TYPE;
	static const int POSITION_USER_TASK;
	static const int NO_OF_START_TIME_INDICATORS;
	static const int NO_OF_END_TIME_INDICATORS;
	static const int NO_OF_NORMAL_IDENTIFIERS;
	static const int NO_OF_DEADLINE_IDENTIFIERS;
	static const int NO_OF_FLOAT_IDENTIFIERS;
	static const int NO_OF_ARCHIVE_IDENTIFIERS;
	static const int DEFAULT_INDEX;
	static const std::string DEADLINE_INDICATOR;
	static const std::string DISPLAY_COMMAND;
	static const std::string SEARCH_COMMAND;
	static const std::string DELETE_COMMAND;
	static const std::string EDIT_COMMAND;
	static const std::string COMPLETE_COMMAND;
	static const std::string INVALID_DATE;
	static const std::string DELIMITERS;
	static const std::string START_TIME_INDICATORS[];
	static const std::string END_TIME_INDICATORS[];
	static const std::string NORMAL_IDENTIFIERS[];
	static const std::string DEADLINE_IDENTIFIERS[];
	static const std::string FLOAT_IDENTIFIERS[];
	static const std::string ARCHIVE_IDENTIFIERS[];
	static const std::string EMPTY;
	static const std::string RECURRING_INDENTIFIER;
	static const std::string RIGID_INDENTIFIER;
	static const std::string ALL_DELIMITER;
	static const std::string DEFAULT_YEAR_SEARCH;
	static const std::string DEFAULT_DAY_SEARCH;



	//SLAP level 1
	bool isRigid(std::string);
	void tokenizeInput(std::string, std::string);
	std::string getCommandType(std::string);
	std::string getUserTask(std::string);
	int getIndexReference(std::string);
	date getStartDate(int&);
	date getEndDate(int&);
	ptime getStartTime(int&);
	ptime getEndTime(int&);
	size_t getEndOfUserTask(std::string);
	size_t getStartOfUserTask(std::string);
	void getRecurringParameter(std::string, std::string&, int&, int&, date&);

	//SLAP level 2
	std::vector<std::string> recurringTokenizer(std::string);
	size_t intToPos(int, std::string);
	bool userTaskParsing(std::string&);
	bool isDeadline(std::string);
	void monthParsingForSearch(std::string&);

	//SLAP level 3
	void frequencyParsing(std::string,int&,std::string&);
	std::string separateRecurringFront(std::string);
	std::string separateRecurringBack(std::string);
	void eraseUserTask(std::string, std::string);
	void assignToday(date&);

public:
	Parser();
	~Parser();
	bool isRecurring(std::string);
	void processCommand(std::string, std::string&, std::string&, date&, date&, ptime&, ptime&, int& indexReference);
	void processCommand(std::string, std::string&,std::string&, std::vector<date>&, std::vector<date>&, std::vector<ptime>&, std::vector<ptime>&);
};

#endif