#ifndef TIMEPARSER_H_
#define TIMEPARSER_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class TimeParser{

private:
	static const int NO_OF_TYPE1_INDICATORS;
	static const int NO_OF_TYPE2_INDICATORS;
	static const int NO_OF_TYPE3_INDICATORS;
	static const std::string TYPE1_INDICATORS[];
	static const std::string TYPE2_INDICATORS[];
	static const std::string TYPE3_INDICATORS[];
	static const int DIFFERENCE_BETWEEN_12HRS_24HRS;
	static const int DIFFERENCE_BETWEEN_SHORT_LONG;
	static const int MAXIMUM_MINUTES;
	static const int SHORT_12HRS;
	static const int LONG_12HRS;
	static const int SHORT_24HRS;
	static const int LONG_24HRS;
	static const ptime INVALID_TIME;
public:
	TimeParser();
	~TimeParser();
	bool isTime(std::string);
	ptime standardTime(std::string);
};

#endif