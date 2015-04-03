
#ifndef DELETETASK_H_
#define DELETETASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class DeleteTask : public ITask {

public:
	DeleteTask(void);
	~DeleteTask(void);
	std::string loadTask(int, Storage&);
	std::string deleteSearchTask(int, Storage&);

private:

};

#endif