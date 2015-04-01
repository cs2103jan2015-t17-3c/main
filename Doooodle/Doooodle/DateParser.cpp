#include "DateParser.h"
using namespace boost::gregorian;
const int DateParser::NUM_IN_FRONT = -1;
const int DateParser::NO_OF_DELIMITERS = 2;
const int DateParser::NO_OF_NEARFUTURE_IDENTIFIERS = 4;
const int DateParser::NO_OF_WEEKDAYS_IDENTIFIERS = 14;
const int DateParser::NO_OF_TIME_IDENTIFIERS = 66;
const int DateParser::NO_OF_MONTH_IDENTIFIERS=48;
const string DateParser::DEFAULT_YEAR = "2015";
const int DateParser::NO_OF_RECURRING_DAILY_DEFAULT = 365;
const int DateParser::NO_OF_RECURRING_WEEKLY_DEFAULT = 52;
const int DateParser::NO_OF_RECURRING_MONTHLY_DEFAULT = 24;
const int DateParser::NO_OF_RECURRING_YEARLY_DEFAULT = 40;
const boost::gregorian::date DateParser::EMPTY_DATE;
const boost::posix_time::ptime DateParser::EMPTY_TIME;
const int DateParser::DEFAULT_DAY=1;
const string DateParser::MONTH_IDENTIFIERS[NO_OF_MONTH_IDENTIFIERS] = {"January","February","March","April","May","June","July","August","Septemper","October","November","December",
                                                                       "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",
																	   "january","february", "march", "april", "may", "june", "july", "august", "septemper", "october", "november", "december",
																	   "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
const string DateParser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                      "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
                                                                      "Tomorrow", "tomorrow", "today" ,"Today",
																	  "January", "February", "March", "April", "May", "June", "July", "August", "Septemper", "October", "November", "December",
																	  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
																	  "january", "february", "march", "april", "may", "june", "july", "august", "septemper", "october", "november", "december",
																	  "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

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

int DateParser::monthToNum(string input){
	if (input == "January" || input == "Jan" || input == "january" || input == "jan"){
		return Jan;
	}
	if (input == "February" || input == "Feb" || input == "february" || input == "feb"){
		return Feb;
	}
	if (input == "March" || input == "Mar" || input == "march" || input == "mar"){
		return Mar;
	}
	if (input == "April" || input == "Apr" || input == "april" || input == "apr"){
		return Apr;
	}
	if (input == "May" || input == "may"){
		return May;
	}
	if (input == "June" || input == "Jun" || input == "june" || input == "jun"){
		return Jun;
	}
	if (input == "July" || input == "Jul" || input == "july" || input == "jul"){
		return Jul;
	}
	if (input == "August" || input == "Aug" || input == "august" || input == "aug"){
		return Aug;
	}
	if (input == "September" || input == "Sep" || input == "september" || input == "sep"){
		return Sep;
	}
	if (input == "October" || input == "Oct" || input == "october" || input == "oct"){
		return Oct;
	}
	if (input == "November" || input == "Nov" || input == "november" || input == "nov"){
		return Nov;
	}
	if (input == "December" || input == "Dec" || input == "december" || input == "dec"){
		return Dec;
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
	removeSlash(input);
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++)
		if (input == TIME_IDENTIFIERS[i]){
			return true;
		}
		else if (((atoi(input.c_str()) >= 101 && input.length() == 4)) || ((atoi(input.c_str()) >= 20150101 && input.length() == 8))){
			return true;
			}
	return false;
}

boost::gregorian::date DateParser::standardiseDate(string before,string input,string after,int& num,int reference){
	date d1;
	date d;
	greg_day day=DEFAULT_DAY;
	date temp(max_date_time);
	date today(day_clock::local_day());
	num = reference;
	for (int i = 0; i < NO_OF_MONTH_IDENTIFIERS; i++){
		if (input == MONTH_IDENTIFIERS[i]){
			greg_month m = monthToNum(MONTH_IDENTIFIERS[i]);
			if (isdigit(before[0])){
				num = NUM_IN_FRONT + reference;
				try{
					greg_day day = atoi(before.c_str());
				}
				catch (...){
					return temp;
				}
				day = atoi(before.c_str());
			}
			else if (isdigit(after[0])){
				try{
					greg_day day = atoi(after.c_str());
				}
				catch (...){
					return temp;
				}
				day = atoi(after.c_str());
			}
			try{
				date d1(atoi(DEFAULT_YEAR.c_str()), m, day);
			}
			catch (...){
				return temp;
			}
			date d1(atoi(DEFAULT_YEAR.c_str()), m, day);
			return d1;
		}
	}

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
	if (atoi(input.c_str()) > 20150101){
		try{
			d = from_undelimited_string(input);
		}
		catch (...){
			return temp;
		}
	}
	else if (input.length() == 4){
		string modified = DEFAULT_YEAR + input;
		try{
			d = from_undelimited_string(modified);
		}
		catch (...){
			return temp;
		}
	}
	
	return d;
}

void DateParser::removeSlash(string& input){
	size_t position;
	for (int i = 0; i < 2; i++){
		for (int i = 0; i < NO_OF_DELIMITERS; i++) {
			position = input.find(DELIMITERS[i]);
			if (position != string::npos) {
				input.erase(input.begin() + position);
			}
		}
	}
	return;
}


void DateParser::completeRecurring(string frequency, vector<boost::gregorian::date>& vecStartDate, vector<boost::gregorian::date>& vecEndDate, vector<boost::posix_time::ptime>& vecStartTime, vector<boost::posix_time::ptime>& vecEndTime){
	date d;
	switch (frequencyCat(frequency)){
	case DAILY:
		for (int i = 0; i < NO_OF_RECURRING_DAILY_DEFAULT; i++){
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}else {
				d = vecStartDate[i] + days(1);
				vecStartDate.push_back(d);
			}
			d = vecEndDate[i]+days(1);
			vecEndDate.push_back(d);
		}
		break;
	case WEEKLY:
		for (int i = 0; i < NO_OF_RECURRING_WEEKLY_DEFAULT; i++){
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}
			else {
				d = vecStartDate[i] + weeks(1);
				vecStartDate.push_back(d);
			}
			d = vecEndDate[i] + weeks(1);
			vecEndDate.push_back(d);
		}
		break;
	case MONTHLY:
		for (int i = 0; i < NO_OF_RECURRING_MONTHLY_DEFAULT; i++){
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}
			else {
				d = vecStartDate[i] + months(1);
				vecStartDate.push_back(d);
			}
			d = vecEndDate[i] + months(1);
			vecEndDate.push_back(d);
		}
		break;
	case YEARLY:
		for (int i = 0; i < NO_OF_RECURRING_YEARLY_DEFAULT; i++){
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}
			else {
				d = vecStartDate[i] + years(1);
				vecStartDate.push_back(d);
			}
			d = vecEndDate[i] + years(1);
			vecEndDate.push_back(d);
		}
	}

	for (int i = 1; i < vecStartDate.size(); i++){
		vecStartTime.push_back(EMPTY_TIME);
		vecEndTime.push_back(EMPTY_TIME);
	}

	//cout << vecStartDate.size() << endl << vecEndDate.size() <<endl<< vecStartTime.size() <<endl<< vecEndTime.size() << endl;
	assert(vecEndTime.size() == vecEndDate.size());
	return;
}

int DateParser::frequencyCat(string input){
	if (input == "everyday" || input == "every day" || input == "daily"){
		return DAILY;
	}
	if (input == "every week" || input == "weekly"){
		return WEEKLY;
	}
	if (input == "every month" || input == "monthly"){
		return MONTHLY;
	}
	if (input == "every year" || input == "yearly"){
		return YEARLY;
	}
}
