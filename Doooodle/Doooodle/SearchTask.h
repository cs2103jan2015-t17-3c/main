
#ifndef SEARCHTASK_H_
#define SEARCHTASK_H_

#include <iostream>
#include "assert.h"
#include "ITask.h"

using namespace std;

class SearchTask {

public:
	SearchTask(void);
	~SearchTask(void);
	vector<string> loadTask(string, boost::gregorian::date, boost::posix_time::ptime, Storage&);

private:

};

#endif