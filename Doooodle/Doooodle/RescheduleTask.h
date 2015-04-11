
//RescheduleTask deals with rescheduling of overdue tasks

#ifndef RESCHEDULETASK_H_
#define RESCHEDULETASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class RescheduleTask : public ITask {

public:
	RescheduleTask(void);
	~RescheduleTask(void);
	std::string loadTask(int, date, date, ptime, ptime, Storage&);

private:

};

#endif