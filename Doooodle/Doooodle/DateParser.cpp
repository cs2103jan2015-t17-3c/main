#include "DateParser.h"
using namespace boost::gregorian;

const string DateParser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                      "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
                                                                      "Tomorrow", "tomorrow", "today" ,"Today"};
const int DateParser::NO_OF_TIME_IDENTIFIERS = 18;
const string DateParser::WEEKDAYS_IDENTIFIERS[NO_OF_WEEKDAYS_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
const int DateParser::NO_OF_WEEKDAYS_IDENTIFIERS = 14;
const string DateParser::NEARFUTURE_IDENTIFIERS[NO_OF_NEARFUTURE_IDENTIFIERS] = { "Tomorrow", "tomorrow", "today", "Today" };
const int DateParser::NO_OF_NEARFUTURE_IDENTIFIERS = 4;
const string DateParser::DELIMITERS[NO_OF_DELIMITERS] = {"\\"};
const int DateParser::NO_OF_DELIMITERS = 1;
DateParser::DateParser(){

}
DateParser::~DateParser(){

}
int DateParser::weekdaysToNum(string input){
	if (input == "Sunday" || "sunday"){
		return Sunday;
	}
	if (input == "Monday" || "monday"){
		return Monday;
	}
	if (input == "Tuesday" || "tuesday"){
		return Tuesday;
	}
	if (input == "Wednesday" || "wednesday"){
		return Wednesday;
	}
	if (input == "Thursday" || "thursday"){
		return Thursday;
	}
	if (input == "Friday" || "friday"){
		return Friday;
	}
	if (input == "Saturday" || "saturday"){
		return Saturday;
	}
}

int DateParser::nearfutureToNum(string input){
	if (input == "Today" || "today"){
		return Today;
	}
	if (input == "Tomorrow" || "tomorrow"){
		return Tomorrow;
	}
}
bool DateParser::isDate(string input){
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++)
		if (input == TIME_IDENTIFIERS[i]){
			return true;
		}
		else if (atoi(input.c_str())>2015){
			removeSlash(input);
			if (atoi(input.c_str()) > 20150000){
				return true;
			}
		}
	return false;
}

boost::gregorian::date DateParser::standardiseDate(string input){
	//date d(2002, Jan, 10);
	//return d;
	//string ud = "20141202";
	date today(day_clock::local_day());
	for (int i = 0; i < NO_OF_WEEKDAYS_IDENTIFIERS; i++){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			greg_weekday wd = weekdaysToNum(WEEKDAYS_IDENTIFIERS[i]);
			//Calculate something like First Sunday after Jan 1, 2002
			first_day_of_the_week_after fdaf(wd);
			date d = fdaf.get_date(date(today));
		}
	}
	for (int i = 0; i < NO_OF_NEARFUTURE_IDENTIFIERS; i++){
		if (input == NEARFUTURE_IDENTIFIERS[i]){
			date d=today+days(nearfutureToNum(NEARFUTURE_IDENTIFIERS[i]));
		}
	}
	if (atoi(input.c_str()) > 20150000){
			date d(from_undelimited_string(input));
		}
	
	//std::cout << to_iso_extended_string(d1) << std::endl;
	return d;
}

void DateParser::removeSlash(string& input){
	size_t position;
	for (int i = 0; i<NO_OF_DELIMITERS; i++) {
		position = input.find(DELIMITERS[i]);
		if (position != string::npos) {
			input.erase(input.begin() + position);
		}
	}
	for (int i = 0; i<NO_OF_DELIMITERS; i++) {
		position = input.find(DELIMITERS[i]);
		if (position != string::npos) {
			input.erase(input.begin() + position);
		}
	}
}