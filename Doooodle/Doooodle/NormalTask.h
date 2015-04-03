
#ifndef NORMALTASK_H_
#define NORMALTASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class NormalTask : public ITask {

public:
	NormalTask(void);
	~NormalTask(void);
	std::string loadTask(std::string, date, date, ptime, ptime, Storage&);

private:

};

#endif