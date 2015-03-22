
#ifndef FLOATINGTASK_H_
#define FLOATINGTASK_H_

#include <iostream>
#include "Task.h"

using namespace std;

class FloatingTask : public Task {

public:
	FloatingTask(void);
	~FloatingTask(void);
	string loadTask(string, Storage&);

private:

};

#endif