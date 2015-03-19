
#ifndef EDITTASK_H_
#define EDITTASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class EditTask {

public:
	EditTask(void);
	~EditTask(void);
	string loadEditTask(int, Storage&);

private:

};

#endif