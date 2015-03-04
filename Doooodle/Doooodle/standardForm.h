#ifndef STANDARDFORM_H_
#define STANDARDFORM_H_

#include <string>
using namespace std;

class standardForm {
public:
	string commandType;
	string task;
	string timeStart;
	string timeEnd;
	string itemToDelete;

	standardForm();
	~standardForm();
};

#endif 