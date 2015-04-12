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



class Storage{
public:
	Storage(void);
	~Storage(void);
	std::string addNormalTask(std::string, date, date, ptime, ptime);
	std::string addDeadlineTask(std::string, date, ptime);
	std::string addFloatingTask(std::string);
	std::vector<std::string> retrieveTopList();
	void sortStorage();
	void writeToFile();
	std::string deleteTask(int);
	std::vector<std::string> searchTask(std::string, date, ptime);
	std::string undoAdd();
	std::string undoDelete();
	std::string undoEdit();
	std::string deleteSearchTask(int);
	std::string editSearchTask(int, std::string, date, date, ptime, ptime);
	std::string editTask(int, std::string, date, date, ptime, ptime);
	std::vector<std::string> retrieveFloatingTask();
	std::string changeDirectory(std::string);
	void initializeTaskDetails(Task&);
	Task initializeNormalTask(std::string, date, date, ptime, ptime);
	std::string taskDetailsFeedback(Task);
	Task initializeDeadlineTask(std::string, date, ptime);
	Task initializeFloatingTask(std::string);
	void registerSearchedStuff(std::vector<Task>::iterator, bool&, std::vector<std::string>&, int&);
	std::vector<std::string> retrieveArchive();
	std::vector<std::string> retrieveOverdue();
	std::string completeAll();
	//no more complete all?
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
	void registerColourIndex(Task);
	std::vector<int> retrieveColourIndex();
	std::string undoComplete();
	void deleteRecurringTask(std::vector<int>);
	int convertToActualIndex(int);
	void updateRecurTask(Task &, std::string, ptime, ptime);
	void updateStandardTask(Task &, std::string, date,date,ptime, ptime);
	std::vector<std::string> reformat(std::vector<std::string>);
	std::vector<std::string> retrieveTopTask();




private:
	std::vector<Task> archivedTask;
	std::vector<Task> activeTask;
	static const std::string MESSAGE_UNDO;
	static const std::string DEFAULT_DIRECTORY;
	static const int DEFAULT_WIDTH;
	static const int DEFAULT_OUTPUT_LENGTH;
    static const int NUMBER_OF_DISPLAY;
	static const int NUMBER_OF_FIRST_THREE_DISPLAY;
	static const int NUMBER_OF_FIRST_FIVE_DISPLAY;
	static const int NUMBER_OF_FLOATING_DISPLAY;
	static const int NUMBER_OF_ARCHIVED_DISPLAY;
	static const std::string DEFAULT_STORAGE_NAME;
	static const std::string DEFAULT_ARCHIVE_NAME;
	static const std::string MESSAGE_CURRENTDIRECTORY_FAIL;
	static const std::string MESSAGE_BUFFER_SMALL;
	static const std::string MESSAGE_SETDIRECTORY_FAIL;
	static const std::string MESSAGE_SETDIRECTORY_SUCCESS;
	static const std::string MESSAGE_WRONG_INDEX;
	static const std::string MESSAGE_DELETE_RECUR;
	static const std::string MESSAGE_UNDO_EMPTY ;
	static const std::string MESSAGE_EDIT_SUCCESS;
	static const std::string MESSAGE_INVALID_RECUR;
	static const std::string MESSAGE_RECUR_SUCCESS;
	static const ptime nonTime;
	static const date nonDate;
	static const date specialDate;
	std::stack<Task> tempTask;
	std::stack<std::string> taskDetailsHistory;
	std::vector<std::vector<Task>::iterator> tempSearchIterator;
	std::vector<std::vector<Task>::iterator> tempOverdueTaskIterator;
	std::stack<int> numberOfUndoActions;
	std::string directoryName;
	std::vector<int> colourIndex;
	bool lastCommandIsDisplay = false;
};

#endif