
#ifndef EDITTASK_H_
#define EDITTASK_H_

#include <iostream>
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class EditTask : public ITask {

public:
	EditTask(void);
	~EditTask(void);
	std::string loadTask(int, std::string, date, date, ptime, ptime, Storage&);
	std::string editSearchTask(int, std::string, date, date, ptime, ptime, Storage&);

private:

};

#endif