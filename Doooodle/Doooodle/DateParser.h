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
	enum nearfuture { Today,Tomorrow };
	static const int NO_OF_TIME_IDENTIFIERS=20;
	static const string TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS];
	static const int NO_OF_WEEKDAYS_IDENTIFIERS=14;
	static const string WEEKDAYS_IDENTIFIERS[NO_OF_WEEKDAYS_IDENTIFIERS];
	static const int NO_OF_NEARFUTURE_IDENTIFIERS=4;
	static const string NEARFUTURE_IDENTIFIERS[NO_OF_NEARFUTURE_IDENTIFIERS];
	int weekdaysToNum(string);
	int nearfutureToNum(string);
public:
	DateParser();
	~DateParser();

	boost::gregorian::date standardiseDate(string);
	bool isDate(string);
};

#endif
