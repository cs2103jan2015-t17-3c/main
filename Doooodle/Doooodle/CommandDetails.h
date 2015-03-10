
#ifndef COMMANDDETAILS_H_
#define COMMANDDETAILS_H_

#include <iostream>
#include <boost/date_time.hpp>

using namespace std;

class CommandDetails {

public:
	string commandType;
	string task;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

	CommandDetails(void);
	~CommandDetails(void);
};

#endif