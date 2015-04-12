//@author A0108562H
#include "CommandDetails.h"

CommandDetails::CommandDetails(void) {
	commandType = "";
	task = "";
	indexReference = 0;
	dateStart = day_clock::local_day();
	dateEnd = day_clock::local_day();
	timeStart = not_a_date_time;
	timeEnd = not_a_date_time;
}

CommandDetails::~CommandDetails(void) {
}