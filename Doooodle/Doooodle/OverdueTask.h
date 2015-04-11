
//OverdueTask deals with completion of tasks

#ifndef OVERDUETASK_H_
#define OVERDUETASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class OverdueTask : public ITask {

public:
	OverdueTask(void);
	~OverdueTask(void);
	std::string loadTask(Storage&);
	std::string completeTask(int, Storage&);
	std::string completeSearchTask(int, Storage&);

private:

};

#endif