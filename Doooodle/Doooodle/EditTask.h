
#ifndef EDITTASK_H_
#define EDITTASK_H_

#include <iostream>
#include "Task.h"

using namespace std;

class EditTask : public Task {

public:
	EditTask(void);
	~EditTask(void);
	string loadTask(int, Storage&);

private:

};

#endif