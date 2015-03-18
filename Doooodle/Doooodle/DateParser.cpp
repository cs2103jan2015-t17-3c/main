#include "DateParser.h"
using namespace boost::gregorian;
const int DateParser::NO_OF_DELIMITERS = 2;
const int DateParser::NO_OF_NEARFUTURE_IDENTIFIERS = 4;
const int DateParser::NO_OF_WEEKDAYS_IDENTIFIERS = 14;
const int DateParser::NO_OF_TIME_IDENTIFIERS = 18;
const int DateParser::NO_OF_MONTH_IDENTIFIERS=48;
const string DateParser::MONTH_IDENTIFIERS[NO_OF_MONTH_IDENTIFIERS] = {"January","February","March","April","May","June","July","August","Septemper","October","November","December"
                                                                       "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
																	   "january","february", "march", "april", "may", "june", "july", "august", "septemper", "october", "november", "december"
																	   "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
const string DateParser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                      "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
                                                                      "Tomorrow", "tomorrow", "today" ,"Today"};

const string DateParser::WEEKDAYS_IDENTIFIERS[NO_OF_WEEKDAYS_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};

const string DateParser::NEARFUTURE_IDENTIFIERS[NO_OF_NEARFUTURE_IDENTIFIERS] = { "Tomorrow", "tomorrow", "today", "Today" };

const string DateParser::DELIMITERS[NO_OF_DELIMITERS] = {"\\","/"};

DateParser::DateParser(){

}
DateParser::~DateParser(){

}
int DateParser::weekdaysToNum(string input){
	if (input == "Sunday" || input=="sunday"){
		return Sunday;
	}
	if (input == "Monday" || input=="monday"){
		return Monday;
	}
	if (input == "Tuesday" || input=="tuesday"){
		return Tuesday;
	}
	if (input == "Wednesday" || input=="wednesday"){
		return Wednesday;
	}
	if (input == "Thursday" || input=="thursday"){
		return Thursday;
	}
	if (input == "Friday" || input=="friday"){
		return Friday;
	}
	if (input == "Saturday" || input=="saturday"){
		return Saturday;
	}
}

int DateParser::nearfutureToNum(string input){
	if (input == "Today" || input=="today"){
		return Today;
	}
	if (input == "Tomorrow" || input=="tomorrow"){
		return Tomorrow;
	}
}

bool DateParser::isDate(string input){
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++)
		if (input == TIME_IDENTIFIERS[i]){
			return true;
		}
		else if (atoi(input.c_str())>=2015){
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
	date d;
	date today(day_clock::local_day());
	for (int i = 0; i < NO_OF_WEEKDAYS_IDENTIFIERS; i++){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			greg_weekday wd = weekdaysToNum(WEEKDAYS_IDENTIFIERS[i]);
			//Calculate something like First Sunday after Jan 1, 2002
			first_day_of_the_week_after fdaf(wd);
			d = fdaf.get_date(date(today));
		}
	}
	for (int i = 0; i < NO_OF_NEARFUTURE_IDENTIFIERS; i++){
		if (input == NEARFUTURE_IDENTIFIERS[i]){
			d=today+days(nearfutureToNum(NEARFUTURE_IDENTIFIERS[i]));
		}
	}
	removeSlash(input);
	if (atoi(input.c_str()) > 20150000){
		try{
			d = from_undelimited_string(input);
		}
		catch (...){
			cout << "wrong date format!" << endl;
		}
	}

	return d;
	//std::cout << to_iso_extended_string(d1) << std::endl;

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