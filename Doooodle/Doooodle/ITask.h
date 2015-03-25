
#ifndef ITASK_H_
#define ITASK_H_

#include <iostream>
#include <boost/date_time.hpp>
#include <assert.h>
#include "Storage.h"

using namespace std;

class ITask {

public:
	virtual ~ITask(void) = 0;
	virtual string loadTask();

protected:
	string task;
	string displayMessage;
	boost::gregorian::date dateStart;
	boost::gregorian::date dateEnd;
	boost::posix_time::ptime timeStart;
	boost::posix_time::ptime timeEnd;

private:
	static const string STRING_TEMPLATE;

};

#endif