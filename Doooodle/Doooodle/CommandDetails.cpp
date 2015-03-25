
#include "CommandDetails.h"

CommandDetails::CommandDetails(void) {
	commandType = "";
	task = "";
	indexReference = 0;
	dateStart = boost::gregorian::day_clock::local_day();
	dateEnd = boost::gregorian::day_clock::local_day();
	timeStart = boost::posix_time::not_a_date_time;
	timeEnd = boost::posix_time::not_a_date_time;
}

CommandDetails::~CommandDetails(void) {
}