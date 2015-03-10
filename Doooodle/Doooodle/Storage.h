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
#include <boost/date_time.hpp>

using namespace std;
using namespace boost;

struct Task{
	string taskDetails;
	boost::gregorian::date startDate;
	boost::gregorian::date endDate;

	posix_time::ptime endTime;
	posix_time::ptime startTime;
};
struct History{
	gregorian::date requestDate;
	posix_time::ptime requestTime;
	Task commandDetails;
};

class Storage{
public:
	Storage(void);
	~Storage(void);
	string addNormalTask(string, boost::gregorian::date, boost::gregorian::date,boost::posix_time::ptime,boost::posix_time::ptime);
	string addDeadlineTask(string, gregorian::date, posix_time::ptime);
	string addFloatTask(string);
	vector<string> retrieveTopFive();
	void sortStorage();
	string writeToFile(string);
	string deleteTask(int);
	vector<string> searchTask(string);

private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
};
















#endif