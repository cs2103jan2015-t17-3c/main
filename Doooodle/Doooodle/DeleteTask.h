
#ifndef DELETETASK_H_
#define DELETETASK_H_

#include <iostream>
#include "Task.h"

using namespace std;

class DeleteTask : public Task {

public:
	DeleteTask(void);
	~DeleteTask(void);
	string loadTask(int, Storage&);

private:

};

#endif