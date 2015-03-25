
#ifndef NORMALTASK_H_
#define NORMALTASK_H_

#include <iostream>
#include "ITask.h"


using namespace std;

class NormalTask : public ITask {

public:
	NormalTask(void);
	~NormalTask(void);
	string loadTask(string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif