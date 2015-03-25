
#ifndef EDITTASK_H_
#define EDITTASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class EditTask : public ITask {

public:
	EditTask(void);
	~EditTask(void);
	string loadTask(int, Storage&);

private:

};

#endif