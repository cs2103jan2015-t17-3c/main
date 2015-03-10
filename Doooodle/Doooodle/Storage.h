#ifndef STORAGE_H_
#define STORAGE_H_

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

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
	string addDeadlineTask(string, string);
	string addFloatTask(string);
	vector<string> retrieveTopFive();
	void sortStorage();
	string writeToFile(string);
	string deleteTask(int);

private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
};
















#endif