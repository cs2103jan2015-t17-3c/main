
#ifndef FLOATINGTASK_H_
#define FLOATINGTASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class FloatingTask {

public:
	string task;

	FloatingTask(void);
	~FloatingTask(void);
	string loadFloatingTask(string, Storage&);

private:

};

#endif