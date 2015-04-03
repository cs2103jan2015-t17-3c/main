
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
#include <sstream>

using namespace boost::gregorian;
using namespace boost::posix_time;

class Parser {

private:
	DateParser dateparser;
	TimeParser timeparser;
	static const int POSITION_COMMAND_TYPE;
	static const std::string INVALID_DATE;
	static const std::string DELIMITERS;
	static const std::string START_TIME_INDICATORS[];
	static const std::string END_TIME_INDICATORS[];
	static const std::string EMPTY;
	static const int NO_OF_START_TIME_INDICATORS;
	static const int NO_OF_END_TIME_INDICATORS;
	static const char RECURRING_INDENTIFIER;
	std::vector<std::string> tokens;

	void tokenizeInput(std::string);
	void rigidTokenizer(std::string);
	std::string getCommandType(std::string);
	int getIndexReference(std::string);
	std::string getUserTask(std::string);
	date getStartDate(int&);
	date getEndDate(int&);
	ptime getStartTime(int&);
	ptime getEndTime(int&);
	size_t intToPos(int,std::string);
	size_t getEndOfUserTask(std::string);
	size_t getStartOfUserTask(std::string);
	void userTaskParsing(std::string&);
	void assignToday(date&);
	bool isRigid(std::string);
	bool isDeadline(std::string);
	std::string getFrequency(std::string);

public:
	Parser();
	~Parser();
	bool isRecurring(std::string);
	void processCommand(std::string, std::string&, std::string&, date&, date&, ptime&, ptime&, int& indexReference);
	void processCommand(std::string, std::string&, std::vector<date>&, std::vector<date>&, std::vector<ptime>&, std::vector<ptime>&);
};

#endif