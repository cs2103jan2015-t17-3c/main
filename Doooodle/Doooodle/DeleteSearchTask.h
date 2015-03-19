
#ifndef DELETESEARCHTASK_H_
#define DELETESEARCHTASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class DeleteSearchTask{ 
public:

	DeleteSearchTask(void);
	~DeleteSearchTask(void);
	string loadDeleteTask(int, Storage&);


private:

};

#endif