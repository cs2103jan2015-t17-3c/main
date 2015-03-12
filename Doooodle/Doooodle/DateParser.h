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
	static const int NO_OF_TIME_IDENTIFIERS;
	static const string TIME_IDENTIFIERS[];
	static const int NO_OF_WEEKDAYS_IDENTIFIERS;
	static const string WEEKDAYS_IDENTIFIERS[];
	static const int NO_OF_NEARFUTURE_IDENTIFIERS;
	static const string NEARFUTURE_IDENTIFIERS[];
	static const int NO_OF_DELIMITERS;
	static const string DELIMITERS[];
	int weekdaysToNum(string);
	int nearfutureToNum(string);
	void removeSlash(string&);
public:
	DateParser();
	~DateParser();

	boost::gregorian::date standardiseDate(string);
	bool isDate(string);
};

#endif
