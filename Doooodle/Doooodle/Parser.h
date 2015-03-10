
#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/date_time.hpp>

using namespace std;

class Parser {

private:
	static const string DELIMITERS;
	static const string START_TIME_INDICATORS[];
	static const string END_TIME_INDICATORS[];
	static const string TIME_IDENTIFIERS[];
	static const int NO_OF_START_TIME_INDICATORS;
	static const int NO_OF_END_TIME_INDICATORS;
	static const int NO_OF_TIME_IDENTIFIERS;


	string getCommandType(string);
	string getUserTask(string);
	boost::gregorian::date getStartDate(string);
	boost::gregorian::date getEndDate(string);
	boost::posix_time::ptime getStartTime(string);
	boost::posix_time::ptime getEndTime(string);
	size_t getEndOfUserTask(string);
	size_t getStartOfUserTask(string);


public:
	Parser();
	~Parser();
	void processCommand(string, string&, string&, boost::gregorian::date&, boost::gregorian::date&, boost::posix_time::ptime&, boost::posix_time::ptime&);
};

#endif