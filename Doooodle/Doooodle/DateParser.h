//@author A0114321B
#ifndef DATEPARSER_H                  
#define DATEPARSER_H

#include <string>
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class DateParser {

private:
	enum frequencyCategory{ DAILY, WEEKLY, MONTHLY, YEARLY };
	enum month { January, February, March, April, May, June, July, August, September,October,November,December};
	enum nearfuture { Today,Tomorrow };
	static const int DEFAULT_DAY;
	static const int NO_OF_RECURRING_DAILY_DEFAULT;
	static const int NO_OF_RECURRING_WEEKLY_DEFAULT;
	static const int NO_OF_RECURRING_MONTHLY_DEFAULT;
	static const int NO_OF_RECURRING_YEARLY_DEFAULT;
	static const int NO_SPECAIL_RECURRENCE;
	static const int SHORT_DATE_LENGTH;
	static const int LONG_DATE_LENGTH;
	static const int MINIMUN_DATE;
	static const int SHORT_MINIMUN_DATE;
	static const int NUM_IN_FRONT;
	static const int WEEKDAY_CYCLE;
	static const int MONTH_CYCLE;
	static const int NEARFUTURE_CYCLE;
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
	static const int NO_OF_DAILY;
	static const std::string DAILY_IDENTIFIERS[];
	static const int NO_OF_WEEKLY;
	static const std::string WEEKLY_IDENTIFIERS[];
	static const int NO_OF_MONTHLY;
	static const std::string MONTHLY_IDENTIFIERS[];
	static const int NO_OF_YEARLY;
	static const std::string YEARLY_IDENTIFIERS[];
	static const std::string DEFAULT_YEAR;
	static const date EMPTY_DATE;
	static const ptime EMPTY_TIME;
	static const date INVALID_DATE;
	static const ptime INVALID_TIME;
	int weekdaysToNum(std::string);
	int nearfutureToNum(std::string);
	void removeSlash(std::string&);
	int getDay(std::string);
	int frequencyCat(std::string);
	date standardiseMonth(std::string, std::string, std::string, int&, int);
	date standardiseWeekday(std::string);
	date standardiseNearFuture(std::string);

public:
	DateParser();
	~DateParser();

	int monthToNum(std::string);
	date standardiseDate(std::string, std::string, std::string,int&,int);
	date standardiseDate(std::string);
	void completeRecurring(std::string, std::vector<date>&, std::vector<date>&, std::vector<ptime>&, std::vector<ptime>&,int,int,date);
	bool isDate(std::string);
};

#endif
