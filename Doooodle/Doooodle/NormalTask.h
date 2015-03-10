
#ifndef NORMALTASK_H_
#define NORMALTASK_H_

#include <iostream>
#include <boost/date_time.hpp>
#include "Storage.h"

using namespace std;

class NormalTask {

public:
	string task;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

	NormalTask(void);
	~NormalTask(void);
	string loadNormalTask(string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif