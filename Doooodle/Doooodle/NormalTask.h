
#ifndef NORMALTASK_H_
#define NORMALTASK_H_

#include <iostream>
#include "Task.h"


using namespace std;

class NormalTask : public Task {

public:
	NormalTask(void);
	~NormalTask(void);
	string loadTask(string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif