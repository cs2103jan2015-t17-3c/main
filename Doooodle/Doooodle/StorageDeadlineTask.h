#ifndef STORAGEDEADLINETASK_H_
#define STORAGEDEADLINETASK_H_

#include<iostream>
#include<sstream>
#include<boost/date_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

struct Task{
	string taskDetails;
	date endDate;
	ptime endTime;
	string taskDisplay;
};

class StorageDeadlineTask{
public:
	StorageDeadlineTask(void);
	~StorageDeadlineTask(void);
	//string addNormalTask(string, date, date, ptime, ptime);
	string addDeadlineTask(string, date, ptime);
	//string addFloatTask(string);
	//vector<string> retrieveTopTen();
	void sortStorage();
	void writeToFile();
	string deleteDeadlineTask(int);
	vector<string> searchTask(string, date, ptime);
	//string undoAdd();
	//string undoDelete();
	//string undoEdit();
	string deleteSearchTask(int);
	//string editSearchTask(int, string, date, date, ptime, ptime);
	//can I do this two together? think about this.
	//string editTask(int, string, date, date, ptime, ptime);
	//vector<string> retrieveFloatingTask();
	//can I do this with retrieve topTen?
	//void changeDirectory(string);
	string initializeTaskDetails(Task);
	//Task initializeNormalTask(string, date, date, ptime, ptime);
	string taskDetailsFeedback(Task);
	//History registerHistory(Task);
	Task initializeDeadlineTask(string, date, ptime);
	//Task initializeFloatTask(string);
	void registerSearchedStuff(vector<Task>::iterator, bool&, vector<string>&, int&);
	//vector<string> retrieveArchive();
	//vector<string> retrieveOverdue();
	//string completeAll();
	//string reschedule(int, date, date, ptime, ptime);
	//vector<string> retrieveCategoricalTask(string);
	///string completeTask(int);
	//string completeSearchTask(int);
	int retrieveDeadlineSize();
	bool task_sorter(Task const&, Task const& );



private:
	vector<Task> archivedDeadlineTask;
	vector<Task> activeDeadlineTask;
	//vector<History> commandHistory;
	static const string MESSAGE_UNDO;
	static const string DEFAULT_DIRECTORY;
	static const int DEFAULT_WIDTH;
	static const int NUMBER_OF_DISPLAY;
	static const int NUMBER_OF_FLOAT_DISPLAY;
	static const int NUMBER_OF_ARCHIVED_DISPLAY;
	static const ptime nonTime;
	static const date nonDate;


	//stack<Task> tempTask;
	//stack<string> taskDetailsHistory;
	//vector<vector<Task>::iterator> tempSearchIterator;
	//vector<vector<Task>::iterator> tempOverdueTaskIterator;

	//string directoryName;
};





#endif