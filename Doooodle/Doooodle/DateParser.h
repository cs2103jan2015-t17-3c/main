#ifndef DATEPARSER_H                  
#define DATEPARSER_H

#include <string>
#include <boost/date_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class DateParser {

private:
	enum weekdays { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
	enum nearfuture { Today=0,Tomorrow };
	static const int NUM_IN_FRONT;
	static const int NO_OF_TIME_IDENTIFIERS;
	static const string TIME_IDENTIFIERS[];
	static const int NO_OF_WEEKDAYS_IDENTIFIERS;
	static const string WEEKDAYS_IDENTIFIERS[];
	static const int NO_OF_NEARFUTURE_IDENTIFIERS;
	static const string NEARFUTURE_IDENTIFIERS[];
	static const int NO_OF_MONTH_IDENTIFIERS;
	static const string MONTH_IDENTIFIERS[];
	static const int NO_OF_DELIMITERS;
	static const string DELIMITERS[];
	static const string DEFAULT_YEAR;
	static const int DEFAULT_DAY;
	int weekdaysToNum(string);
	int monthToNum(string);
	int nearfutureToNum(string);
	void removeSlash(string&);
	int getDay(string);

public:
	DateParser();
	~DateParser();

	boost::gregorian::date standardiseDate(string, string, string,int&,int);
	bool isDate(string);
};

#endif
