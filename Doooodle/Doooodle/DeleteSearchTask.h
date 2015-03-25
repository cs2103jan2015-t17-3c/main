
#ifndef DELETESEARCHTASK_H_
#define DELETESEARCHTASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class DeleteSearchTask : public ITask{ 
public:

	DeleteSearchTask(void);
	~DeleteSearchTask(void);
	string loadTask(int, Storage&);

private:

};

#endif