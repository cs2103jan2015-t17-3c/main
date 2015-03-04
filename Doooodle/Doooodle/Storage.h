#ifndef STORAGE_H_
#define STORAGE_H_

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Task{
	string taskDetails;
	string startTime;
	string endTime;
};
struct History{
	string requestTime;
	Task commandDetails;
};

class Storage{
public:
	Storage(void);
	~Storage(void);
	string addNormalTask(string, string, string);
	string addDueTask(string, string);
	string addFloatTask(string);
private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
};
















#endif