
#ifndef RESCHEDULETASK_H_
#define RESCHEDULETASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class RescheduleTask : public ITask {

public:
	RescheduleTask(void);
	~RescheduleTask(void);
	string loadTask(int, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif