
#ifndef EDITSEARCHTASK_H_
#define EDITSEARCHTASK_H_

#include <iostream>
#include "ITask.h"

using namespace std;

class EditSearchTask : public ITask {

public:
	EditSearchTask(void);
	~EditSearchTask(void);
	string loadTask(int, string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime, Storage&);

private:

};

#endif