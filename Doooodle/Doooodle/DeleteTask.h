
#ifndef DELETETASK_H_
#define DELETETASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class DeleteTask : public ITask {

public:
	DeleteTask(void);
	~DeleteTask(void);
	string loadTask(int, Storage&);

private:

};

#endif