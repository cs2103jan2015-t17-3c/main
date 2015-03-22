
#ifndef SEARCHTASK_H_
#define SEARCHTASK_H_

#include <iostream>
#include "Task.h"

using namespace std;

class SearchTask : public Task {

public:
	SearchTask(void);
	~SearchTask(void);
	vector<string> loadTask(string, Storage&);

private:

};

#endif