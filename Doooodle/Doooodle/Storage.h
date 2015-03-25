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
#include <fstream>

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
	string commandDisplay;
};



class Storage{
public:
	Storage(void);
	~Storage(void);
	string addNormalTask(string, boost::gregorian::date, boost::gregorian::date,boost::posix_time::ptime,boost::posix_time::ptime);
	string addDeadlineTask(string, gregorian::date, posix_time::ptime);
	string addFloatTask(string);
	vector<string> retrieveTopTen();
	void sortStorage();
	void writeToFile();
	string deleteTask(int);
	vector<string> searchTask(string,boost::gregorian::date,boost::posix_time::ptime);
	string undoAdd();
	string undoDelete();
	string undoEdit();
    string deleteSearchTask(int);
	string redoDelete();
	string redoAdd();
	string editTask(int, string, boost::gregorian::date, boost::gregorian::date, boost::posix_time::ptime, boost::posix_time::ptime);
	vector<string> displayFloatingTask();
	void changeDirectory(string);
private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
	
	static const string MESSAGE_UNDO;
	static const string MESSAGE_REDO;
	static const string DEFAULT_DIRECTORY;
	stack<Task> tempTask;
	stack<string> taskDetailsHistory;
	vector<vector<Task>::iterator> tempSearchIterator;
	stack<Task> redoAddTask;
	stack<Task> redoDeleteTask;
	string directoryName;
};
















#endif