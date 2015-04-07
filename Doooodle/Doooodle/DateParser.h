#ifndef DATEPARSER_H                  
#define DATEPARSER_H

#include <string>
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class DateParser {

private:
	enum frequencyCategory{ DAILY, WEEKLY, MONTHLY, YEARLY };
	enum weekdays { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
	enum nearfuture { Today=0,Tomorrow };
	static const int NUM_IN_FRONT;
	static const int NO_OF_TIME_IDENTIFIERS;
	static const std::string TIME_IDENTIFIERS[];
	static const int NO_OF_WEEKDAYS_IDENTIFIERS;
	static const std::string WEEKDAYS_IDENTIFIERS[];
	static const int NO_OF_NEARFUTURE_IDENTIFIERS;
	static const std::string NEARFUTURE_IDENTIFIERS[];
	static const int NO_OF_MONTH_IDENTIFIERS;
	static const std::string MONTH_IDENTIFIERS[];
	static const int NO_OF_DELIMITERS;
	static const std::string DELIMITERS[];
	static const std::string DEFAULT_YEAR;
	static const int DEFAULT_DAY;
	static const int NO_OF_RECURRING_DAILY_DEFAULT;
	static const int NO_OF_RECURRING_WEEKLY_DEFAULT;
	static const int NO_OF_RECURRING_MONTHLY_DEFAULT;
	static const int NO_OF_RECURRING_YEARLY_DEFAULT;
	static const date EMPTY_DATE;
	static const ptime EMPTY_TIME;
	int weekdaysToNum(std::string);
	int nearfutureToNum(std::string);
	void removeSlash(std::string&);
	int getDay(std::string);
	int frequencyCat(std::string);

public:
	DateParser();
	~DateParser();

	int monthToNum(std::string);
	boost::gregorian::date standardiseDate(std::string, std::string, std::string,int&,int);
	boost::gregorian::date standardiseDate(std::string);
	void completeRecurring(std::string, std::vector<date>&, std::vector<date>&, std::vector<ptime>&, std::vector<ptime>&,int,date);
	bool isDate(std::string);
};

#endif
