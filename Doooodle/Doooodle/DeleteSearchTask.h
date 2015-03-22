
#ifndef DELETESEARCHTASK_H_
#define DELETESEARCHTASK_H_

#include <iostream>
#include "Task.h"

using namespace std;

class DeleteSearchTask : public Task{ 
public:

	DeleteSearchTask(void);
	~DeleteSearchTask(void);
	string loadTask(int, Storage&);

private:

};

#endif