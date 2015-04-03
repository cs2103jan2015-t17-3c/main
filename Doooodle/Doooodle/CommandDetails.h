
#ifndef COMMANDDETAILS_H_
#define COMMANDDETAILS_H_

#include <iostream>
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class CommandDetails {

public:
	std::string commandType;		//for "add", "delete", "edit", "undo" etc.
	std::string task;		//to store details for add, edit, reschedule etc.
	int indexReference;		//to store reference index for delete, edit, reschedule etc.
	date dateStart;
	date dateEnd;
	ptime timeStart;
	ptime timeEnd;
	//following vectors for recurring events to store future recurrence
	std::vector<date> dateStartRecur;
	std::vector<date> dateEndRecur;
	std::vector<ptime> timeStartRecur;
	std::vector<ptime> timeEndRecur;

	CommandDetails(void);
	~CommandDetails(void);
};

#endif