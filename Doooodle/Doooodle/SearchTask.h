
//SearchTask deals with searching of tasks

#ifndef SEARCHTASK_H_
#define SEARCHTASK_H_

#include <iostream>
#include "assert.h"
#include "ITask.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class SearchTask {

public:
	SearchTask(void);
	~SearchTask(void);
	std::vector<std::string> loadTask(std::string, date, ptime, Storage&);

private:

};

#endif