
#ifndef DEADLINETASK_H_
#define DEADLINETASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class DeadlineTask : public ITask {

public:
	DeadlineTask(void);
	~DeadlineTask(void);
	string loadTask(string, boost::gregorian::date, boost::posix_time::ptime, Storage&);

private:

};

#endif