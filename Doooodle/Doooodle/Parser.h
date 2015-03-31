
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


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Parser {

private:
	static const int POSITION_COMMAND_TYPE;
	static const string INVALID_DATE;
	static const string DELIMITERS;
	static const string START_TIME_INDICATORS[];
	static const string END_TIME_INDICATORS[];
	static const string TIME_IDENTIFIERS[];
	static const string EMPTY;
	static const int NO_OF_START_TIME_INDICATORS;
	static const int NO_OF_END_TIME_INDICATORS;
	static const int NO_OF_TIME_IDENTIFIERS;
	static const char RECURRING_INDENTIFIER;
	vector<string> tokens;

	void tokenizeInput(string);
	string getCommandType(string);
	int getIndexReference(string);
	string getUserTask(string);
	boost::gregorian::date getStartDate(int&);
	boost::gregorian::date getEndDate(int&);
	boost::posix_time::ptime getStartTime(int&);
	boost::posix_time::ptime getEndTime(int&);
	size_t intToPos(int,string);
	size_t getEndOfUserTask(string);
	size_t getStartOfUserTask(string);
	void userTaskParsing(string&);
	void assignToday(boost::gregorian::date&);
	bool isDeadline(string);

public:
	Parser();
	~Parser();
	bool isRecurring(string);
	void processCommand(string, string&, string&, boost::gregorian::date&, boost::gregorian::date&, boost::posix_time::ptime&, boost::posix_time::ptime&, int& indexReference);
	void processCommand(string, string&, vector<boost::gregorian::date>&, vector<boost::gregorian::date>&, vector<boost::posix_time::ptime>&, vector<boost::posix_time::ptime>&);
};

#endif