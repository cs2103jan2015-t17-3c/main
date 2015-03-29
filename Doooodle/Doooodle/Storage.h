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
using namespace boost::gregorian;
using namespace boost::posix_time;

enum TYPE_OF_TASK{
	DEADLINE, FLOAT, NORMAL
};

struct Task{
	string taskDetails;
	date startDate;
	date endDate;
	ptime endTime;
	ptime startTime;
	TYPE_OF_TASK taskType;
	string taskDisplay;
};

struct History{
	date requestDate;
	ptime requestTime;
	Task commandDetails;
	string commandDisplay;
};

class Storage{
public:
	Storage(void);
	~Storage(void);
	string addNormalTask(string, date, date,ptime,ptime);
	string addDeadlineTask(string,date,ptime);
	string addFloatTask(string);
	vector<string> retrieveTopTen();
	void sortStorage();
	void writeToFile();
	string deleteTask(int);
	vector<string> searchTask(string,date,ptime);
	string undoAdd();
	string undoDelete();
	string undoEdit();
    string deleteSearchTask(int);
	string editSearchTask(int, string, date, date, ptime, ptime);
	//can I do this two together? think about this.
	string editTask(int, string, date, date, ptime, ptime);
	vector<string> retrieveFloatingTask();
	//can I do this with retrieve topTen?
	void changeDirectory(string);
	string initializeTaskDetails(Task);
	Task initializeNormalTask(string, date, date, ptime, ptime);
	string taskDetailsFeedback(Task);
	History registerHistory(Task);
	Task initializeDeadlineTask(string, date, ptime);
	Task initializeFloatTask(string);
	void registerSearchedStuff(vector<Task>::iterator, bool&, vector<string>&,int&);
	vector<string> retrieveArchive();
	vector<string> retrieveOverdue();
	void completeAll();
	string reschedule(int, date, date, ptime, ptime);
	vector<string> retrieveCategoricalTask(string);




private:
	vector<Task> archivedTask;
	vector<Task> activeTask;
	vector<History> commandHistory;
	static const string MESSAGE_UNDO;
	static const string DEFAULT_DIRECTORY;
	static const int DEFAULT_WIDTH;
    static const int NUMBER_OF_DISPLAY;
	static const int NUMBER_OF_FLOAT_DISPLAY;
	static const int NUMBER_OF_ARCHIVED_DISPLAY;


	stack<Task> tempTask;
	stack<string> taskDetailsHistory;
	vector<vector<Task>::iterator> tempSearchIterator;
	vector<vector<Task>::iterator> tempOverdueTaskIterator;

	string directoryName;
};

#endif