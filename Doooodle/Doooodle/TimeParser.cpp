#include "TimeParser.h"

const int TimeParser::NO_OF_TYPE1_INDICATORS = 2;
const int TimeParser::NO_OF_TYPE2_INDICATORS = 21;
const int TimeParser::NO_OF_TYPE3_INDICATORS = 4;
const int TimeParser::DIFFERENCE_BETWEEN_12HRS_24HRS = 12;
const string TimeParser::TYPE1_INDICATORS[NO_OF_TYPE1_INDICATORS] = {":", "."};
const string TimeParser::TYPE2_INDICATORS[NO_OF_TYPE2_INDICATORS] = {"am", "Am", "AM", "aM", "pm", "Pm", "PM", "pM", "hr", "hrs", "HR", "HRS", "Hr", "Hrs", "hours", "hour", "HOURS", "Hours", "clock", ":", "."};
const string TimeParser::TYPE3_INDICATORS[NO_OF_TYPE3_INDICATORS] = {"pm", "pM", "PM", "Pm"};
const boost::posix_time::ptime TimeParser::INVALID_TIME(boost::date_time::max_date_time);

TimeParser::TimeParser(){
}

TimeParser::~TimeParser(){
}

bool TimeParser::isTime(string input) {
	size_t position = 0;
	for(int i = 0; i<NO_OF_TYPE2_INDICATORS; i++){
		position = input.find(TYPE2_INDICATORS[i]);
		if (position != string::npos){
			return true;
		}
	}
	return false;
}
//if not_a_date_time is returned, the input is not a date or time
//if max_date_time is returned, the date time format of the input is invalid
boost::posix_time::ptime TimeParser::standardTime(string input) {
	boost::posix_time::ptime time(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(0) + boost::posix_time::minutes(0));
	boost::posix_time::ptime d(boost::posix_time::not_a_date_time);
	size_t position = 0;
	bool isColonDotCase = false;
	bool isPmCase = false;
	if (!isTime(input)){
		return d;
	}

	//to identify . or : and to remove them to use atoi
	for(int i=0; ((i<NO_OF_TYPE1_INDICATORS) && (!isColonDotCase)); i++) {
		position = input.find(TYPE1_INDICATORS[i]);
		if (position != string::npos) {
			isColonDotCase = true;
		}
	}

	if(isColonDotCase) {
		input.erase(input.begin()+position);
	}

	//to identify pm case (e.g. 3.15pm) so that 12 hours can be added to make it reflect 24hr clock
	for(int i=0; ((i<NO_OF_TYPE3_INDICATORS) && (!isPmCase)); i++) {
		position = input.find(TYPE3_INDICATORS[i]);
		if (position != string::npos) {
			isPmCase = true;
		}
	}

	//transfer number(integer) to ptime
	int timeInt = atoi(input.c_str());
	if(timeInt<=24 && !isPmCase) {
		time += boost::posix_time::hours(timeInt);
	}else if (timeInt <=12 && isPmCase){
		time += boost::posix_time::hours(timeInt + DIFFERENCE_BETWEEN_12HRS_24HRS);
	}else if((timeInt<=2400) && (!isPmCase) && (timeInt%100<=60)) {
		time += boost::posix_time::hours(timeInt/100) + boost::posix_time::minutes(timeInt%100);
	}else if((timeInt<=1200) && (isPmCase) && (timeInt%100<=60)) {
		time += boost::posix_time::hours(DIFFERENCE_BETWEEN_12HRS_24HRS + (timeInt / 100)) + boost::posix_time::minutes(timeInt % 100);
	}else{
		time = INVALID_TIME;
	}

	return time;
}
