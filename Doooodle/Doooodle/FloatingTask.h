
#ifndef FLOATINGTASK_H_
#define FLOATINGTASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class FloatingTask : public ITask {

public:
	FloatingTask(void);
	~FloatingTask(void);
	string loadTask(string, Storage&);

private:

};

#endif