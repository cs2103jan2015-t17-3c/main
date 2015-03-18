
#ifndef DELETETASK_H_
#define DELETETASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class DeleteTask {

public:
	DeleteTask(void);
	~DeleteTask(void);
	vector<string> loadDeleteTask(int, Storage&);

private:

};

#endif