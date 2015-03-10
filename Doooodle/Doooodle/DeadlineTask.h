
#ifndef DEADLINETASK_H_
#define DEADLINETASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class DeadlineTask {

public:
	string task;
	string timeEnd;

	DeadlineTask(void);
	~DeadlineTask(void);
	string loadDeadlineTask(string, string, Storage&);

private:

};

#endif