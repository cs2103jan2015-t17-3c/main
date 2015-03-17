
#ifndef SEARCHTASK_H_
#define SEARCHTASK_H_

#include <iostream>
#include "Storage.h"

using namespace std;

class SearchTask {

public:
	SearchTask(void);
	~SearchTask(void);
	vector<string> loadSearchTask(string, Storage&);

private:

};

#endif