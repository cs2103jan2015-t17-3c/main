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
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>

//using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

enum TYPE_OF_TASK{
	DEADLINE, FLOATING, NORMAL
};

enum TYPE_OF_SPECIAL_TASK{
	NONRECUR,RECUR
};
struct Task{
	std::string taskDetails;
	date startDate;
	date endDate;
	ptime endTime;
	ptime startTime;
	TYPE_OF_TASK taskType;
	TYPE_OF_SPECIAL_TASK specialTaskType;
	std::string taskDisplay;
};

struct History{
	date requestDate;
	ptime requestTime;
	Task commandDetails;
	std::string commandDisplay;
};

class Storage{
	
public:
	Storage(void);
	~Storage(void);
	std::string addNormalTask(std::string, date, date, ptime, ptime);
	std::string addDeadlineTask(std::string, date, ptime);
	std::string addFloatingTask(std::string);
	std::vector<std::string> retrieveTopFifteen();
	void sortStorage();
	void writeToFile();
	std::string deleteTask(int);
	std::vector<std::string> searchTask(std::string, date, ptime);
	std::string undoAdd();
	std::string undoDelete();
	std::string undoEdit();
	std::string deleteSearchTask(int);
	std::string editSearchTask(int, std::string, date, date, ptime, ptime);
	//can I do this two together? think about this.
	std::string editTask(int, std::string, date, date, ptime, ptime);
	std::vector<std::string> retrieveFloatingTask();
	//can I do this with retrieve topTen?
	void changeDirectory(std::string);
	std::string initializeTaskDetails(Task);
	Task initializeNormalTask(std::string, date, date, ptime, ptime);
	std::string taskDetailsFeedback(Task);
	History registerHistory(Task);
	Task initializeDeadlineTask(std::string, date, ptime);
	Task initializeFloatingTask(std::string);
	void registerSearchedStuff(std::vector<Task>::iterator, bool&, std::vector<std::string>&, int&);
	std::vector<std::string> retrieveArchive();
	std::vector<std::string> retrieveOverdue();
	std::string completeAll();
	std::string reschedule(int, date, date, ptime, ptime);
	std::vector<std::string> retrieveCategoricalTask(std::string);
	std::string completeTask(int);
	std::string completeSearchTask(int);
	std::string addRecurringTask(std::string, std::vector<date>, std::vector<date>, std::vector<ptime>, std::vector<ptime>);
	int retrieveDeadlineSize();
	int retrieveNormalSize();
	int retrieveFloatingSize();
	int searchTaskDisplay(std::string);
	void loadTasks(std::string , std::vector<Task>&);
	std::vector<int> findRecurIndex(std::string, TYPE_OF_SPECIAL_TASK);




private:
	
	std::vector<Task> archivedTask;
	std::vector<Task> activeTask;
	std::vector<History> commandHistory;
	static const std::string MESSAGE_UNDO;
	static const std::string DEFAULT_DIRECTORY;
	static const int DEFAULT_WIDTH;
    static const int NUMBER_OF_DISPLAY;
	static const int NUMBER_OF_FLOATING_DISPLAY;
	static const int NUMBER_OF_ARCHIVED_DISPLAY;


	std::stack<Task> tempTask;
	std::stack<std::string> taskDetailsHistory;
	std::vector<std::vector<Task>::iterator> tempSearchIterator;
	std::vector<std::vector<Task>::iterator> tempOverdueTaskIterator;

	std::string directoryName;
};

#endif