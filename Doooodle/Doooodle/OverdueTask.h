
#ifndef OVERDUETASK_H_
#define OVERDUETASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class OverdueTask : public ITask {

public:
	OverdueTask(void);
	~OverdueTask(void);
	string loadTask(Storage&);
	string completeTask(int, Storage&);
	string completeSearchTask(int, Storage&);

private:

};

#endif