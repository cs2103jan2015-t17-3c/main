#include "TimeParser.h"

const int TimeParser::NO_OF_TYPE1_INDICATORS = 4;
const int TimeParser::NO_OF_TYPE2_INDICATORS = 4;
const int TimeParser::NO_OF_TYPE3_INDICATORS = 10;
const int TimeParser::NO_OF_TYPE4_INDICATORS = 2;
const int TimeParser::NO_OF_TYPE5_INDICATORS = 1;
const int TimeParser::NO_OF_TYPE6_INDICATORS = 2;
const int TimeParser::NO_OF_TYPE7_INDICATORS = 22;
const string TimeParser::TYPE1_INDICATORS[NO_OF_TYPE1_INDICATORS] = {"am", "Am", "AM", "aM"};
const string TimeParser::TYPE2_INDICATORS[NO_OF_TYPE2_INDICATORS] = {"pm", "Pm", "PM", "pM"};
const string TimeParser::TYPE3_INDICATORS[NO_OF_TYPE3_INDICATORS] = {"hr", "hrs", "HR", "HRS", "Hr", "Hrs", "hours", "hour", "HOURS", "Hours"};
const string TimeParser::TYPE4_INDICATORS[NO_OF_TYPE4_INDICATORS] = {"today", "Today"};
const string TimeParser::TYPE5_INDICATORS[NO_OF_TYPE5_INDICATORS] = {"clock"};
const string TimeParser::TYPE6_INDICATORS[NO_OF_TYPE6_INDICATORS] = {":", "."};
const string TimeParser::TYPE7_INDICATORS[NO_OF_TYPE7_INDICATORS] = {"am", "Am", "AM", "aM", "pm", "Pm", "PM", "pM", "hr", "hrs", "HR", "HRS", "Hr", "Hrs", "hours", "hour", "HOURS", "Hours", "today", "Today", "clock", ":"};

TimeParser::TimeParser(){
}

TimeParser::~TimeParser(){
}

bool TimeParser::isTime(string input) {
	size_t position = 0;
	for(int i = 0; i<NO_OF_TYPE7_INDICATORS; i++){
		position = input.find(TYPE7_INDICATORS[i]);
		if (position != string::npos){
			return true;
		}
	}
	return false;
}

boost::posix_time::ptime TimeParser::standardTime(string input) {
	boost::posix_time::ptime time(boost::gregorian::date(), boost::posix_time::hours(0) + boost::posix_time::minutes(0));
	size_t position = 0;
	bool isColonDotCase = false;
	for(int i=0; ((i<NO_OF_TYPE6_INDICATORS) && (!isColonDotCase)); i++) {
		position = input.find(TYPE6_INDICATORS[i]);
		if (position != string::npos) {
			isColonDotCase = true;
		}
	}

	if(isColonDotCase) {
		input.erase(input.begin()+position);
	}
	int timeInt = atoi(input.c_str());
	if(timeInt<100) {
		time += boost::posix_time::hours(timeInt);
	} else if(timeInt<10000) {
		time += boost::posix_time::hours(timeInt/100) + boost::posix_time::minutes(timeInt%100);
	}
	return time;
}
/*
boost::posix_time::ptime TimeParser::standardTime(string input) {
	size_t positionA = 0;
	size_t positionB = 0;
	bool timeIndicatorFound = false;
//type 6
	for(int i = 0; ((!timeIndicatorFound) && (i<NO_OF_TYPE6_INDICATORS)); i++){
		positionB = input.find(TYPE6_INDICATORS[i]);
		if (positionB != string::npos){
			timeIndicatorFound = true;
		}
		if (timeIndicatorFound) {
			positionA = positionB;
			while(!isdigit(input[positionB])) {
				positionB++;
			}
			while(!isdigit(input[positionA])) {
				positionA--;
			}
			int timeInt = atoi(input.substr(positionA, positionB-positionA).c_str);
			boost::posix_time::ptime t6(input.substr(positionA, positionB-positionA).c_str);
			return t6;
		}
	}
//type 3
	for(int i = 0; ((!timeIndicatorFound) && (i<NO_OF_TYPE3_INDICATORS)); i++){
		positionB = input.find(TYPE3_INDICATORS[i]);
		if (positionB != string::npos){
			timeIndicatorFound = true;
		}
		if (timeIndicatorFound) {
			while(!isdigit(input[positionB])) {
				positionB--;
			}
			positionA = positionB;
			while(isdigit(input[positionA])) {
				positionA--;
			}
			positionA++;
			int timeInt = atoi(input.substr(positionA, positionB-positionA).c_str);
			boost::posix_time::ptime t3(input.substr(positionA, positionB-positionA).c_str);
			return t3;
		}
	}
//type 4
	for(int i = 0; ((!timeIndicatorFound) && (i<NO_OF_TYPE4_INDICATORS)); i++){
		positionB = input.find(TYPE4_INDICATORS[i]);
		if (positionB != string::npos){
			timeIndicatorFound = true;
		}
		if (timeIndicatorFound) {
			boost::posix_time::ptime t4(2359);
			return t4;
		}
	}
//type 5
	for(int i = 0; ((!timeIndicatorFound) && (i<NO_OF_TYPE5_INDICATORS)); i++){
		positionB = input.find(TYPE5_INDICATORS[i]);
		if (positionB != string::npos){
			timeIndicatorFound = true;
		}
		if (timeIndicatorFound) {
			while(!isdigit(input[positionB])) {
				positionB--;
			}
			int timeInt = atoi(input.substr[positionB].c_str);
			boost::posix_time::ptime t5(input.substr(positionA, positionB-positionA).c_str);
			return t5;
		}
	}
}
*/
/*	for (int i = 0; ((!timeIndicatorFound) && (i<NO_OF_TYPE1_INDICATORS)); i++){
		positionB = input.find(TYPE1_INDICATORS[i]);
		if (positionB != string::npos){
			timeIndicatorFound = true;
		}
	}
	if (timeIndicatorFound) {
		while(!isdigit(input[positionB])) {
			positionB--;
		}
		positionA = positionB;
		while(isdigit(input[positionA])) {
			positionA--;
		}
		positionA++;
		int timeInt = atoi(input.substr(positionA, positionB-positionA).c_str);
		if(timeInt<13) {
			boost::posix_time::ptime t(boost::posix_time::hours(timeInt));
		}
		return t;
	}*/
}
