#include "DateParser.h"

const int DateParser::NO_OF_DAILY=3;
const std::string DateParser::DAILY_IDENTIFIERS[NO_OF_DAILY] = {"everyday","every day","daily"};
const int DateParser::NO_OF_WEEKLY=2;
const std::string DateParser::WEEKLY_IDENTIFIERS[NO_OF_WEEKLY] = {"every week","weekly"};
const int DateParser::NO_OF_MONTHLY=2;
const std::string DateParser::MONTHLY_IDENTIFIERS[NO_OF_MONTHLY] = {"every month","monthly"};
const int DateParser::NO_OF_YEARLY=2;
const std::string DateParser::YEARLY_IDENTIFIERS[NO_OF_YEARLY] = { "every year", "yearly" };
const int DateParser::NUM_IN_FRONT = -1;
const int DateParser::SHORT_DATE_LENGTH = 4;
const int DateParser::LONG_DATE_LENGTH = 8;
const int DateParser::NO_OF_DELIMITERS = 2;
const int DateParser::NO_SPECAIL_RECURRENCE=-1;
const int DateParser::NO_OF_NEARFUTURE_IDENTIFIERS = 4;
const int DateParser::NO_OF_WEEKDAYS_IDENTIFIERS = 14;
const int DateParser::NO_OF_TIME_IDENTIFIERS = 66;
const int DateParser::WEEKDAY_CYCLE=7;
const int DateParser::MONTH_CYCLE = 12;
const int DateParser::NEARFUTURE_CYCLE = 2;
const int DateParser::NO_OF_MONTH_IDENTIFIERS=48;
const int DateParser::MINIMUN_DATE = 19000100;
const int DateParser::SHORT_MINIMUN_DATE = 0100;
const std::string DateParser::DEFAULT_YEAR = "2015";
const int DateParser::NO_OF_RECURRING_DAILY_DEFAULT = 365;
const int DateParser::NO_OF_RECURRING_WEEKLY_DEFAULT = 52;
const int DateParser::NO_OF_RECURRING_MONTHLY_DEFAULT = 24;
const int DateParser::NO_OF_RECURRING_YEARLY_DEFAULT = 40;
const date DateParser::EMPTY_DATE;
const ptime DateParser::EMPTY_TIME;
const date DateParser::INVALID_DATE(max_date_time);
const ptime DateParser::INVALID_TIME(max_date_time);
const int DateParser::DEFAULT_DAY=1;
const std::string DateParser::MONTH_IDENTIFIERS[NO_OF_MONTH_IDENTIFIERS] = {"January","February","March","April","May","June","July","August","Septemper","October","November","December",
                                                                       "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",
																	   "january","february", "march", "april", "may", "june", "july", "august", "septemper", "october", "november", "december",
																	   "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
const std::string DateParser::TIME_IDENTIFIERS[NO_OF_TIME_IDENTIFIERS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                                                      "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
                                                                      "Tomorrow", "tomorrow", "today" ,"Today",
																	  "January", "February", "March", "April", "May", "June", "July", "August", "Septemper", "October", "November", "December",
																	  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
																	  "january", "february", "march", "april", "may", "june", "july", "august", "septemper", "october", "november", "december",
																	  "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

const std::string DateParser::WEEKDAYS_IDENTIFIERS[NO_OF_WEEKDAYS_IDENTIFIERS] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

const std::string DateParser::NEARFUTURE_IDENTIFIERS[NO_OF_NEARFUTURE_IDENTIFIERS] = { "today", "Tomorrow","Today", "tomorrow"};

const std::string DateParser::DELIMITERS[NO_OF_DELIMITERS] = {"\\","/"};

DateParser::DateParser(){

}
DateParser::~DateParser(){

}
int DateParser::weekdaysToNum(std::string input){
	for (int i = Sunday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Sunday;
		}
	}
	for (int i = Monday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Monday;
		}
	}
	for (int i = Tuesday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Tuesday;
		}
	}
	for (int i = Wednesday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Wednesday;
		}
	}
	for (int i = Thursday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Thursday;
		}
	}
	for (int i = Friday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Friday;
		}
	}
	for (int i = Saturday; i < NO_OF_WEEKDAYS_IDENTIFIERS; i = i + WEEKDAY_CYCLE){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			return Saturday;
		}
	}
}

int DateParser::monthToNum(std::string input){
	for (int i = January; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Jan;
		}
	}
	for (int i = February; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Feb;
		}
	}
	for (int i = March; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Mar;
		}
	}
	for (int i = April; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Apr;
		}
	}
	for (int i = May; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return boost::date_time::months_of_year::May;
		}
	}
	for (int i = June; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Jun;
		}
	}
	for (int i = July; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Jul;
		}
	}
	for (int i = August; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Aug;
		}
	}
	for (int i = September; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Sep;
		}
	}
	for (int i = October; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Oct;
		}
	}
	for (int i = November; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Nov;
		}
	}	
	for (int i = December; i < NO_OF_MONTH_IDENTIFIERS; i = i + MONTH_CYCLE){
		if (input == MONTH_IDENTIFIERS[i]){
			return Dec;
		}
	}
}

int DateParser::nearfutureToNum(std::string input){
	for (int i = Today; i < NO_OF_NEARFUTURE_IDENTIFIERS; i = i + NEARFUTURE_CYCLE){
		if (input == NEARFUTURE_IDENTIFIERS[i]){
			return Today;
		}
	}
	for (int i = Tomorrow; i < NO_OF_NEARFUTURE_IDENTIFIERS; i = i + NEARFUTURE_CYCLE){
		if (input == NEARFUTURE_IDENTIFIERS[i]){
			return Tomorrow;
		}
	}
}

bool DateParser::isDate(std::string input){
	removeSlash(input);
	for (int i = 0; i < NO_OF_TIME_IDENTIFIERS; i++)
		if (input == TIME_IDENTIFIERS[i]){
			return true;
		}else if (((atoi(input.c_str()) > SHORT_MINIMUN_DATE && input.length() == SHORT_DATE_LENGTH)) || ((atoi(input.c_str()) >= MINIMUN_DATE && input.length() == LONG_DATE_LENGTH))){
			return true;
			}
	return false;
}

date DateParser::standardiseDate(std::string input){
	date d;
	removeSlash(input);
	if (atoi(input.c_str()) > MINIMUN_DATE){
		try{
			d = from_undelimited_string(input);
		}
		catch (...){
			return INVALID_DATE;
		}
	}else if (input.length() == SHORT_DATE_LENGTH){
		std::string modified = DEFAULT_YEAR + input;
		try{
			d = from_undelimited_string(modified);
		}
		catch (...){
			return INVALID_DATE;
		}
	}

	return d;
}

date DateParser::standardiseDate(std::string before,std::string input,std::string after,int& num,int reference){
	if (standardiseMonth(before, input, after, num, reference) != EMPTY_DATE){
		return standardiseMonth(before, input, after, num, reference);
	}
	if (standardiseWeekday(input) != EMPTY_DATE){
		return standardiseWeekday(input);
	}
	if (standardiseNearFuture(input) != EMPTY_DATE){
		return 	standardiseNearFuture(input);
	}
	return standardiseDate(input);
	/*for (int i = 0; i < NO_OF_MONTH_IDENTIFIERS; i++){
		if (input == MONTH_IDENTIFIERS[i]){
			greg_month m = monthToNum(MONTH_IDENTIFIERS[i]);
			if (isdigit(before[0])){
				num = NUM_IN_FRONT + reference;
				try{
					greg_day day = atoi(before.c_str());
				}
				catch (...){
					return INVALID_DATE;
				}
				day = atoi(before.c_str());
			}
			else if (isdigit(after[0])){
				try{
					greg_day day = atoi(after.c_str());
				}
				catch (...){
					return INVALID_DATE;
				}
				day = atoi(after.c_str());
			}
			try{
				date d1(atoi(DEFAULT_YEAR.c_str()), m, day);
			}
			catch (...){
				return INVALID_DATE;
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
	if (atoi(input.c_str()) > MINIMUN_DATE){
		try{
			d = from_undelimited_string(input);
		}
		catch (...){
			return INVALID_DATE;
		}
	}
	else if (input.length() == SHORT_DATE_LENGTH){
		std::string modified = DEFAULT_YEAR + input;
		try{
			d = from_undelimited_string(modified);
		}
		catch (...){
			return INVALID_DATE;
		}
	}*/
}

void DateParser::removeSlash(std::string& input){
	size_t position;
	for (int i = 0; i < 2; i++){
		for (int i = 0; i < NO_OF_DELIMITERS; i++) {
			position = input.find(DELIMITERS[i]);
			if (position != std::string::npos) {
				input.erase(input.begin() + position);
			}
		}
	}
	return;
}


void DateParser::completeRecurring(std::string frequency, std::vector<date>& vecStartDate, std::vector<date>& vecEndDate, std::vector<ptime>& vecStartTime, std::vector<ptime>& vecEndTime, int recurrence,int interval, date finishDate){
	date d;
	switch (frequencyCat(frequency)){
	case DAILY:
		if (recurrence == NO_SPECAIL_RECURRENCE){
			recurrence = NO_OF_RECURRING_DAILY_DEFAULT;
		}
		for (int i = 0; i < recurrence; i++){
			d = vecEndDate[i] + days(interval);
			if ((finishDate != EMPTY_DATE && d < finishDate) || finishDate == EMPTY_DATE){
				vecEndDate.push_back(d);
			}else{
				break;
			}
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}else {
				d = vecStartDate[i] + days(interval);
				vecStartDate.push_back(d);
			}
		}
		break;
	case WEEKLY:
		if (recurrence == NO_SPECAIL_RECURRENCE){
			recurrence = NO_OF_RECURRING_WEEKLY_DEFAULT;
		}
		for (int i = 0; i < recurrence; i++){
			d = vecEndDate[i] + weeks(interval);
			if ((finishDate != EMPTY_DATE && d < finishDate) || finishDate == EMPTY_DATE){
				vecEndDate.push_back(d);
			}else{
				break;
			}
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}else {
				d = vecStartDate[i] + weeks(interval);
				vecStartDate.push_back(d);
			}
		}
		break;
	case MONTHLY:
		if (recurrence == NO_SPECAIL_RECURRENCE){
			recurrence = NO_OF_RECURRING_MONTHLY_DEFAULT;
		}
		for (int i = 0; i < recurrence; i++){
			d = vecEndDate[i] + months(interval);
			if ((finishDate != EMPTY_DATE && d < finishDate) || finishDate == EMPTY_DATE){
				vecEndDate.push_back(d);
			}else{
				break;
			}
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}else {
				d = vecStartDate[i] + months(interval);
				vecStartDate.push_back(d);
			}
		}
		break;
	case YEARLY:
		if (recurrence == NO_SPECAIL_RECURRENCE){
			recurrence = NO_OF_RECURRING_YEARLY_DEFAULT;
		}
		for (int i = 0; i < recurrence; i++){
			d = vecEndDate[i] + years(interval);
			if ((finishDate != EMPTY_DATE && d < finishDate) || finishDate == EMPTY_DATE){
				vecEndDate.push_back(d);
			}else{
				break;
			}
			if (vecStartDate[i] == EMPTY_DATE){
				vecStartDate.push_back(EMPTY_DATE);
			}else {
				d = vecStartDate[i] + years(interval);
				vecStartDate.push_back(d);
			}
		}
	}
	for (int i = 1; i < vecStartDate.size(); i++){
		vecStartTime.push_back(vecStartTime[0]);
		vecEndTime.push_back(vecEndTime[0]);
	}
	assert(vecEndTime.size() == vecEndDate.size());
	return;
}

int DateParser::frequencyCat(std::string input){
	for (int i = 0; i < NO_OF_DAILY; i++){
		if (input == DAILY_IDENTIFIERS[i]){
			return DAILY;
		}
	}
	for (int i = 0; i < NO_OF_WEEKLY; i++){
		if (input == WEEKLY_IDENTIFIERS[i]){
			return WEEKLY;
		}
	}
	for (int i = 0; i < NO_OF_MONTHLY; i++){
		if (input == MONTHLY_IDENTIFIERS[i]){
			return MONTHLY;
		}
	}
	for (int i = 0; i < NO_OF_YEARLY; i++){
		if (input == YEARLY_IDENTIFIERS[i]){
			return YEARLY;
		}
	}
}

date DateParser::standardiseMonth(std::string before, std::string input, std::string after, int& num, int reference){
	greg_day day = DEFAULT_DAY;
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
					return INVALID_DATE;
				}
				day = atoi(before.c_str());
			}else if (isdigit(after[0])){
				try{
					greg_day day = atoi(after.c_str());
				}
				catch (...){
					return INVALID_DATE;
				}
				day = atoi(after.c_str());
			}
			try{
				date d1(atoi(DEFAULT_YEAR.c_str()), m, day);
			}
			catch (...){
				return INVALID_DATE;
			}
			date d1(atoi(DEFAULT_YEAR.c_str()), m, day);
			return d1;
		}
	}
	return EMPTY_DATE;
}

date DateParser::standardiseWeekday(std::string input){
	date today(day_clock::local_day());
	for (int i = 0; i < NO_OF_WEEKDAYS_IDENTIFIERS; i++){
		if (input == WEEKDAYS_IDENTIFIERS[i]){
			greg_weekday wd = weekdaysToNum(WEEKDAYS_IDENTIFIERS[i]);
			//Calculate something like First Sunday after Jan 1, 2002
			first_day_of_the_week_after fdaf(wd);
			date d = fdaf.get_date(date(today));
			return d;
		}
	}
	return EMPTY_DATE;
}

date DateParser::standardiseNearFuture(std::string input){
	date today(day_clock::local_day());
	for (int i = 0; i < NO_OF_NEARFUTURE_IDENTIFIERS; i++){
		if (input == NEARFUTURE_IDENTIFIERS[i]){
			int test = nearfutureToNum(NEARFUTURE_IDENTIFIERS[i]);
			date d = today + days(nearfutureToNum(NEARFUTURE_IDENTIFIERS[i]));
			return d;
		}
	}
	return EMPTY_DATE;
}