
#ifndef TASK_H_
#define TASK_H_

#include <iostream>
#include <boost/date_time.hpp>
#include "Storage.h"

using namespace std;

class Task {

public:
	Task(void);
	~Task(void);
	string loadTask(string, Storage&);

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