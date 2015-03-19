
#ifndef TIMEPARSER_H_
#define TIMEPARSER_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <boost/date_time.hpp>

using namespace std;

class TimeParser{

private:
	static const int NO_OF_TYPE1_INDICATORS;
	static const int NO_OF_TYPE2_INDICATORS;
	static const int NO_OF_TYPE3_INDICATORS;
	static const string TYPE1_INDICATORS[];
	static const string TYPE2_INDICATORS[];
	static const string TYPE3_INDICATORS[];
	static const int DIFFERENCE_BETWEEN_12HRS_24HRS;

public:
	TimeParser();
	~TimeParser();
	bool isTime(string);
	boost::posix_time::ptime standardTime(string);
};

#endif