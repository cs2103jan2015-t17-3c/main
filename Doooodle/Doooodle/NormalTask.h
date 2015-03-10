
#ifndef NORMALTASK_H_
#define NORMALTASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class NormalTask {

public:
	string task;
	string timeStart;
	string timeEnd;

	NormalTask(void);
	~NormalTask(void);
	void loadNormalTask(string, string, string, Storage&);

private:

};

#endif