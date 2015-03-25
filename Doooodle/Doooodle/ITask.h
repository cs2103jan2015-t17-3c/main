
#ifndef ITASK_H_
#define ITASK_H_

#include <iostream>
#include <boost/date_time.hpp>
#include "Storage.h"

using namespace std;

class ITask {

public:
	virtual ~ITask(void) = 0;
	virtual string loadTask(string, Storage&);

protected:
	string task;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

private:
	static const string STRING_TEMPLATE;

};

#endif