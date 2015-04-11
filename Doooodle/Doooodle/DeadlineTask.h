
//DeadlineTask deals with deadline tasks

#ifndef DEADLINETASK_H_
#define DEADLINETASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class DeadlineTask : public ITask {

public:
	DeadlineTask(void);
	~DeadlineTask(void);
	std::string loadTask(std::string, date, ptime, Storage&);

private:

};

#endif