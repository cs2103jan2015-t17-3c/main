
#ifndef DEADLINETASK_H_
#define DEADLINETASK_H_

#include <iostream>
#include <boost/date_time.hpp>
#include "Storage.h"

using namespace std;

class DeadlineTask {

public:
	string task;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeEnd;

	DeadlineTask(void);
	~DeadlineTask(void);
	string loadDeadlineTask(string, boost::gregorian::date, boost::posix_time::ptime, Storage&);

private:

};

#endif