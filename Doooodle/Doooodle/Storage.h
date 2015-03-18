#ifndef STORAGE_H_
#define STORAGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <boost/date_time.hpp>
#include <iomanip>
#include <stack>

using namespace std;
using namespace boost;


enum TYPE_OF_TASK{
	DEADLINE, FLOAT, NORMAL
};


struct Task{
	string taskDetails;
	boost::gregorian::date startDate;
	boost::gregorian::date endDate;

	posix_time::ptime endTime;
	posix_time::ptime startTime;
	TYPE_OF_TASK taskType;
	string taskDisplay;
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
	void writeToFile();
	string deleteTask(int);
	vector<string> searchTask(string);
	string undoAdd();
	string undoDelete();
	string undoEdit();

private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
	static const string MESSAGE_UNDO;
	Task tempTask;
	stack<string> taskDetailsHistory;
};
















#endif