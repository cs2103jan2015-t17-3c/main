#include "TimeParser.h"

const int TimeParser::NO_OF_TYPE1_INDICATORS = 2;
const int TimeParser::NO_OF_TYPE2_INDICATORS = 21;
const int TimeParser::NO_OF_TYPE3_INDICATORS = 4;
const int TimeParser::DIFFERENCE_BETWEEN_12HRS_24HRS = 12;
const int TimeParser::DIFFERENCE_BETWEEN_SHORT_LONG = 100;
const int TimeParser::SHORT_12HRS=12;
const int TimeParser::MAXIMUM_MINUTES = 60;
const int TimeParser::LONG_12HRS=1200;
const int TimeParser::SHORT_24HRS=24;
const int TimeParser::LONG_24HRS=2400;
const std::string TimeParser::TYPE1_INDICATORS[NO_OF_TYPE1_INDICATORS] = {":", "."};
const std::string TimeParser::TYPE2_INDICATORS[NO_OF_TYPE2_INDICATORS] = {"am", "Am", "AM", "aM", "pm", "Pm", "PM", "pM", "hr", "hrs", "HR", "HRS", "Hr", "Hrs", "hours", "hour", "HOURS", "Hours", "clock", ":", "."};
const std::string TimeParser::TYPE3_INDICATORS[NO_OF_TYPE3_INDICATORS] = {"pm", "pM", "PM", "Pm"};
const ptime TimeParser::INVALID_TIME(max_date_time);

TimeParser::TimeParser(){
}

TimeParser::~TimeParser(){
}

bool TimeParser::isTime(std::string input) {
	size_t position = 0;
	for(int i = 0; i<NO_OF_TYPE2_INDICATORS; i++){
		position = input.find(TYPE2_INDICATORS[i]);
		if (position != std::string::npos && isdigit(input[0])){
			return true;
		}
	}
	return false;
}
//if not_a_date_time is returned, the input is not a date or time
//if max_date_time is returned, the date time format of the input is invalid
ptime TimeParser::standardTime(std::string input) {
	ptime time(date(day_clock::local_day()), hours(0) + minutes(0));
	ptime d(not_a_date_time);
	size_t position = 0;
	bool isColonDotCase = false;
	bool isPmCase = false;
	if (!isTime(input)){
		return d;
	}
	//to identify . or : and to remove them to use atoi
	for(int i=0; ((i<NO_OF_TYPE1_INDICATORS) && (!isColonDotCase)); i++) {
		position = input.find(TYPE1_INDICATORS[i]);
		if (position != std::string::npos) {
			isColonDotCase = true;
		}
	}
	if(isColonDotCase) {
		input.erase(input.begin()+position);
	}
	//to identify pm case (e.g. 3.15pm) so that 12 hours can be added to make it reflect 24hr clock
	for(int i=0; ((i<NO_OF_TYPE3_INDICATORS) && (!isPmCase)); i++) {
		position = input.find(TYPE3_INDICATORS[i]);
		if (position != std::string::npos) {
			isPmCase = true;
		}
	}
	//transfer number(integer) to ptime
	int timeInt = atoi(input.c_str());
	if (timeInt <= SHORT_24HRS && !isPmCase) {
		time += hours(timeInt);
	}else if (timeInt <= SHORT_12HRS && isPmCase){
		time += hours(timeInt + DIFFERENCE_BETWEEN_12HRS_24HRS);
	}else if ((timeInt <= LONG_24HRS) && (!isPmCase) && (timeInt % DIFFERENCE_BETWEEN_SHORT_LONG <= MAXIMUM_MINUTES)) {
		time += hours(timeInt / DIFFERENCE_BETWEEN_SHORT_LONG) + minutes(timeInt%DIFFERENCE_BETWEEN_SHORT_LONG);
	}else if ((timeInt <= LONG_12HRS) && (isPmCase) && (timeInt % DIFFERENCE_BETWEEN_SHORT_LONG <= MAXIMUM_MINUTES)) {
		time += hours(DIFFERENCE_BETWEEN_12HRS_24HRS + (timeInt / DIFFERENCE_BETWEEN_SHORT_LONG)) + minutes(timeInt % DIFFERENCE_BETWEEN_SHORT_LONG);
	}else{
		time = INVALID_TIME;
	}
	return time;
}
