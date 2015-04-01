
#ifndef COMMANDDETAILS_H_
#define COMMANDDETAILS_H_

#include <iostream>
#include <boost/date_time.hpp>

using namespace std;

class CommandDetails {

public:
	string commandType;		//for "add", "delete", "edit", "undo" etc.
	string task;		//to store details for add, edit, reschedule etc.
	int indexReference;		//to store reference index for delete, edit, reschedule etc.
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;
	//following vectors for recurring events to store future recurrence
	vector<boost::gregorian::date> dateStartRecur;
	vector<boost::gregorian::date> dateEndRecur;
	vector<	boost::posix_time::ptime> timeStartRecur;
	vector<	boost::posix_time::ptime> timeEndRecur;

	CommandDetails(void);
	~CommandDetails(void);
};

#endif