//@author A0108562H
//FloatTask deals with floating tasks

#ifndef FLOATINGTASK_H_
#define FLOATINGTASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class FloatingTask : public ITask {

public:
	FloatingTask(void);
	~FloatingTask(void);
	std::string loadTask(std::string, Storage&);

private:

};

#endif