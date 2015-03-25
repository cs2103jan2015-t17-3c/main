
#ifndef EDITTASK_H_
#define EDITTASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class EditTask : public ITask {

public:
	EditTask(void);
	~EditTask(void);
	string loadTask(int, string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif