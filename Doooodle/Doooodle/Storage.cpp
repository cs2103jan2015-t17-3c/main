#include "Storage.h"

const date Storage::nonDate(not_a_date_time);
const ptime Storage::nonTime(not_a_date_time);
const date Storage::specialDate(1900, Jan, 10);
const std::string Storage::MESSAGE_UNDO = "Undo is successfully performed";
const std::string Storage::MESSAGE_UNDO_EMPTY = "Nothing to undo.\n";
const std::string Storage::DEFAULT_DIRECTORY = "dooodle.txt";
const std::string Storage::DEFAULT_STORAGE_NAME = "storageFile.txt";
const std::string Storage::DEFAULT_ARCHIVE_NAME = "archiveFile.txt";
const std::string Storage::MESSAGE_CURRENTDIRECTORY_FAIL = "GetCurrentDirectory failed.\n";
const std::string Storage::MESSAGE_BUFFER_SMALL = "Buffer too small; need more characters\n";
const std::string Storage::MESSAGE_SETDIRECTORY_FAIL = "SetCurrentDirectory failed\n";
const std::string Storage::MESSAGE_SETDIRECTORY_SUCCESS = "Set current directory to ";
const std::string Storage::MESSAGE_WRONG_INDEX = "Wrong index.\n";
const std::string Storage::MESSAGE_DELETE_RECUR = "Recurring task is successfully deleted.\n";
const std::string Storage::MESSAGE_EDIT_SUCCESS = "task is successfully edited\n";
const std::string Storage::MESSAGE_INVALID_RECUR = "Invalid recurring task.\n";
const std::string Storage::MESSAGE_RECUR_SUCCESS = "Recurring Task is successfully added!\n";
const std::string Storage::MESSAGE_COMPLETE_ALL = "all overdue tasks are completed.\n";
const int Storage::DEFAULT_WIDTH = 25;
const int Storage::DEFAULT_OUTPUT_LENGTH = 30;
const int Storage::NUMBER_OF_FIRST_THREE_DISPLAY = 3;
const int Storage::NUMBER_OF_FIRST_FIVE_DISPLAY = 5;
const int Storage::NUMBER_OF_DISPLAY = 15;
const int Storage::NUMBER_OF_FLOATING_DISPLAY = 12;
const int Storage::NUMBER_OF_ARCHIVED_DISPLAY = 20;

Storage::Storage(void){
	loadTasks(DEFAULT_STORAGE_NAME, activeTask);
	loadTasks(DEFAULT_ARCHIVE_NAME, archivedTask);
}

void Storage::loadTasks(std::string filename, std::vector<Task>& target ){
	std::ifstream fl_h; 
	fl_h.open(filename);
	if (fl_h.good()){
		int num = 1;
		Task tempTask;
		std::string dummy;
		while (!fl_h.eof()){
			getline(fl_h, tempTask.taskDetails);
			if (tempTask.taskDetails == ""){
				break;
			}
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				date dateStart(from_undelimited_string(dummy));
				tempTask.startDate = dateStart;
			}else{
				tempTask.startDate = nonDate;
			}
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				date dateEnd(from_undelimited_string(dummy));
				tempTask.endDate = dateEnd;
			}else{
				tempTask.endDate = nonDate;
			}
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				ptime timeStart(from_iso_string(dummy));
				tempTask.startTime = timeStart;
			}else{
				tempTask.startTime = nonTime;
			}
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				ptime timeEnd(from_iso_string(dummy));
				tempTask.endTime = timeEnd;
			}else{
				tempTask.endTime = nonTime;
			}
			getline(fl_h, tempTask.taskDisplay);
			getline(fl_h, dummy);
			if (dummy == "0"){
				tempTask.taskType = DEADLINE;
			}else if (dummy == "1"){
				tempTask.taskType = FLOATING;
			}else{
				tempTask.taskType = NORMAL;
			}
			getline(fl_h, dummy);
			if (dummy == "0"){
				tempTask.specialTaskType = NONRECUR;
			}else if (dummy == "1"){
				tempTask.specialTaskType = RECUR;
			}
			target.push_back(tempTask);
		}
	}
	fl_h.close();
};

Storage::~Storage(void){
};

int Storage::retrieveDeadlineSize(){
	int count = 0;
	for (int i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == DEADLINE){
			count++;
		}
	}
	return count;
}

int Storage::retrieveNormalSize(){
	int count = 0;
	for (int i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == NORMAL){
			count++;
		}
	}
	return count;
}

int Storage::retrieveFloatingSize(){
	int count = 0;
	for (int i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == FLOATING){
			count++;
		}
	}
	return count;
}



History Storage::registerHistory(Task temp){
	History trace;
	ptime currentTime;
	currentTime = second_clock::local_time();
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	std::ostringstream addCommandDisplay;
	addCommandDisplay << temp.taskDisplay << " " << currentTime << std::endl;
	trace.commandDisplay = addCommandDisplay.str();
	return trace;
}



void Storage::initializeTaskDetails(Task &temp){
	std::ostringstream outputTask;
	date currentDate(day_clock::local_day());
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					if (temp.startDate.year() != currentDate.year() || temp.endDate.year() != currentDate.year()){
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
					}else{
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
					}
				}else{
					if (temp.startDate.year() != currentDate.year() || temp.endDate.year() != currentDate.year()){
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << std::setfill(' ') << std::setw(6) << "]";
					}else{
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << std::setfill(' ') << std::setw(6) << "]";
					}
				}
			}else{
				if (temp.endTime != nonTime){
					if (temp.startDate.year() != currentDate.year() || temp.endDate.year() != currentDate.year()){
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startDate.year() << std::setfill(' ') << std::setw(9) << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
					}else{
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << std::setfill(' ') << std::setw(9) << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
				}
			}else{
					if (temp.startDate.year() != currentDate.year() || temp.endDate.year() != currentDate.year()){
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startDate.year() << "      ]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << "      ]";
					}else{
						outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.startDate.day() << " " << temp.startDate.month() << "      ]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << "      ]";
					}
				}
			}
		}else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				if (temp.endDate.year() != currentDate.year()){
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [      " << std::right << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
				}else{
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [      " << std::right << std::setfill(' ') << std::setw(2) << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
				}
			}
		}
	}else if (temp.taskType == DEADLINE){
			if (temp.endTime == nonTime){
				if (temp.endDate.year() != currentDate.year()){
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << "      ]";
				}else{
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << "      ]";
				}
			}else{
				if (temp.endDate.year() != currentDate.year()){
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endDate.year() << ", " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
				}else{
					outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << std::right << std::setfill(' ') << std::setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << std::setfill(' ') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "]";
				}
			}
		}else if (temp.taskType == FLOATING){
			outputTask << std::left << std::setw(DEFAULT_WIDTH) << temp.taskDetails;
			}
	temp.taskDisplay = outputTask.str();
}

std::string Storage::taskDetailsFeedback(Task temp){
	std::ostringstream outputTask;
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().hours() << ":" << std::setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
				}else{
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << "      ] successfully added.\n";
				}
			}else{
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << "      ]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
				}else{
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << "      ]-[" << temp.endDate.day() << " " << temp.endDate.month() << "      ] successfully added.\n";
				}
			}
		}else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				outputTask << "Normal task: " << temp.taskDetails << " [      " << temp.startTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
			}
		}
	}else if (temp.taskType == DEADLINE){
		if (temp.endTime == nonTime){
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate.day() << " " << temp.endDate.month() << " successfully added.\n";
		}else{
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << std::setfill('0') << std::setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
		}
	}else if(temp.taskType == FLOATING){
		outputTask << "Floating task: " << temp.taskDetails << " successfully added.\n";
	}
	return outputTask.str();
}

Task Storage::initializeNormalTask(std::string task, date startDate, date endDate, ptime startTime, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = startDate;
	temp.endDate = endDate;
	temp.startTime = startTime;
	temp.endTime = endTime;
	temp.taskType = NORMAL;
	temp.specialTaskType = NONRECUR;
	initializeTaskDetails(temp);
	return temp;
}



std::string Storage::addNormalTask(std::string task, date startDate, date endDate, ptime startTime, ptime endTime){
	Task temp = initializeNormalTask(task, startDate, endDate, startTime, endTime);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	numberOfUndoActions.push(1);
	History trace = registerHistory(temp);
	addHistory.push_back(trace);  //logging (defensive coding)
	return taskDetailsFeedback(temp);
};

Task Storage::initializeDeadlineTask(std::string task, date endDate, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = endDate;
	temp.startTime = nonTime;
	temp.endTime = endTime;
	temp.taskType = DEADLINE;
	temp.specialTaskType = NONRECUR;
	initializeTaskDetails(temp);
	return temp;
}

std::string Storage::addDeadlineTask(std::string task, date endDate, ptime endTime){
	Task temp = initializeDeadlineTask(task,endDate,endTime);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	numberOfUndoActions.push(1);
	History trace = registerHistory(temp);
	addHistory.push_back(trace);  //logging (defensive coding)
	return taskDetailsFeedback(temp);
};

Task Storage::initializeFloatingTask(std::string task){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = nonDate;
	temp.startTime = nonTime;
	temp.endTime = nonTime;
	temp.taskType = FLOATING;
	temp.specialTaskType = NONRECUR;
	initializeTaskDetails(temp);
	return temp;
}

std::string Storage::addFloatingTask(std::string task){
	Task temp = initializeFloatingTask(task);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	addHistory.push_back(trace);  //logging (defensive coding)
	numberOfUndoActions.push(1);
	return taskDetailsFeedback(temp);
};


void Storage::registerColourIndex(Task temp){
	date currentDate(day_clock::local_day());
	ptime currentTime(second_clock::local_time());
	if (temp.taskType == DEADLINE){
		if (temp.endDate < currentDate){
			colourIndex.push_back(0);
		}else if (temp.endDate == currentDate && temp.endTime < currentTime){
				colourIndex.push_back(0);
			}else{
				colourIndex.push_back(1);
			}
	 }else if (temp.taskType == NORMAL){
		if(temp.startDate < currentDate){
			colourIndex.push_back(0);
		}else if (temp.startDate == currentDate && temp.startTime < currentTime){
			colourIndex.push_back(0);
		}else
			colourIndex.push_back(2);
	 }else if (temp.taskType == FLOATING){
		colourIndex.push_back(3);
	 }
	}


std::vector<std::string> Storage::retrieveTopList(){
	lastCommandIsDisplay = false;
	colourIndex.clear();
	std::vector<int> sortedTaskIndex;
	std::vector<std::string> topTasks;
	int i;
	int count = 0;
	for (i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == DEADLINE){
			sortedTaskIndex.push_back(i);
			registerColourIndex(activeTask[i]);
			count++;
		}
		if (count == NUMBER_OF_FIRST_THREE_DISPLAY){
			break;
		}
	}
	for (i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == NORMAL){
			sortedTaskIndex.push_back(i);
			registerColourIndex(activeTask[i]);
			count++;
		}
		if (count == NUMBER_OF_FIRST_FIVE_DISPLAY){
			break;
		}
	}
		for (i = 0; i < activeTask.size(); i++){
			bool repeat = false;
			for (int j = 0; j < sortedTaskIndex.size(); j++){
				if (i == sortedTaskIndex[j] || activeTask[i].taskType == FLOATING){
					repeat = true;
					break;
				}
			}
			if (!repeat && sortedTaskIndex.size()!=0){
				sortedTaskIndex.push_back(i);
				registerColourIndex(activeTask[i]);
				count++;
			}
		}
	for (int j = 0; j < sortedTaskIndex.size(); j++){
		std::ostringstream oneTask;
		oneTask << std::setfill('0') << std::setw(2) << j + 1 << ". " << activeTask[sortedTaskIndex[j]].taskDisplay;
		topTasks.push_back(oneTask.str());
	}
	return topTasks;
}

std::vector<std::string> Storage::retrieveTopTask(){
	std::vector<std::string> topTasks = retrieveTopList();
	return reformat(topTasks);
}

std::vector<std::string> Storage::retrieveOverdue(){
	std::vector<std::string> displayOverdueTasks;
	tempOverdueTaskIterator.clear();
	std::vector<Task>::iterator iter;
	date currentDate(day_clock::local_day());
	ptime currentTime(second_clock::local_time());
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		if (iter->endDate < currentDate){
			displayOverdueTasks.push_back(iter->taskDisplay);
			tempOverdueTaskIterator.push_back(iter);
		}else if (iter->endDate == currentDate && iter->endTime < currentTime){
				displayOverdueTasks.push_back(iter->taskDisplay);
				tempOverdueTaskIterator.push_back(iter);
		}
	}
	return displayOverdueTasks;
}


std::string Storage::completeAll(){
int index;
	for (index = 0; index < tempOverdueTaskIterator.size(); index++){
		archivedTask.push_back(*tempOverdueTaskIterator[index]);
		activeTask.erase(tempOverdueTaskIterator[index]);
	}
	return MESSAGE_COMPLETE_ALL;
}

/*//do we still have this?
std::string Storage::reschedule(int index, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	using namespace std;
	Task temporaryTask = *tempOverdueTaskIterator[index - 1];
	activeTask.erase(tempOverdueTaskIterator[index-1]);
	if (tempStartDate != temporaryTask.startDate && tempStartDate != nonDate){
		temporaryTask.startDate = tempStartDate;
	}
	if (tempEndDate != temporaryTask.endDate && tempEndDate != nonDate){
		temporaryTask.endDate = tempEndDate;
	}
	if (tempStartTime != temporaryTask.startTime && tempStartTime != nonTime){
		temporaryTask.startTime = tempStartTime;
	}
	if (tempEndTime != temporaryTask.endTime && tempEndTime != nonTime){
		temporaryTask.endTime = tempEndTime;
	}
	initializeTaskDetails(temporaryTask);
	activeTask.push_back(temporaryTask);
	return "task is successfuly rescheduled";
}
*/

std::vector<std::string> Storage::retrieveCategoricalTask(std::string typeTask){
	colourIndex.clear();
	std::vector<std::string> displayedTasks;
	if (typeTask == "normal"){
		for (int i = 0; i < activeTask.size(); i++){
			if (activeTask[i].taskType == NORMAL){
				registerColourIndex(activeTask[i]);
				std::ostringstream oneTask;
				oneTask << std::setfill('0') << std::setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
				displayedTasks.push_back(oneTask.str());
			}
		}   
		lastCommandIsDisplay = true;
		return displayedTasks;
	}
	if (typeTask == "floating"){
			for (int i = 0; i < activeTask.size(); i++){
				if (activeTask[i].taskType == FLOATING){
					std::ostringstream oneTask;
					registerColourIndex(activeTask[i]);
					oneTask << std::setfill('0') << std::setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
					displayedTasks.push_back(oneTask.str());
				}
			}
			lastCommandIsDisplay = true;
			return displayedTasks;
	}
	if (typeTask == "deadline"){
			for (int i = 0; i < activeTask.size(); i++){
				if (activeTask[i].taskType == DEADLINE){
					registerColourIndex(activeTask[i]);
					std::ostringstream oneTask;
					oneTask << std::setfill('0') << std::setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
					displayedTasks.push_back(oneTask.str());
				}
	        }
			lastCommandIsDisplay = true;
	        return displayedTasks;
	}
	if (typeTask == "archive"){
			for (int i = 0; i < archivedTask.size() && i < NUMBER_OF_ARCHIVED_DISPLAY; i++){
				colourIndex.push_back(4);
				std::ostringstream oneTask;
				oneTask << i + 1 << ". " << archivedTask[i].taskDisplay;
				displayedTasks.push_back(oneTask.str());
			}
			return displayedTasks;
	}
}

std::vector<std::string> Storage::retrieveFloatingTask(){
	std::vector<std::string> TopTasks;
	int displayIndex = 1+retrieveDeadlineSize() + retrieveNormalSize();
	for (int i = 0; i < activeTask.size() ; i++){
		if (activeTask[i].taskType == FLOATING){
			std::ostringstream floatingTaskDisplay;
			floatingTaskDisplay << std::setfill('0') << std::setw(2) << displayIndex << ". " << activeTask[i].taskDisplay;
			TopTasks.push_back(floatingTaskDisplay.str());
			displayIndex++;
		}
	}
	return TopTasks;
}

bool task_sorter(Task const& lhs, Task const& rhs){
	if (lhs.taskType == NORMAL && rhs.taskType == NORMAL){
		if (lhs.startDate != rhs.startDate){
			return lhs.startDate < rhs.startDate;
		}
		return lhs.startTime < rhs.startTime;
	} else if (lhs.taskType == NORMAL && rhs.taskType == DEADLINE){
		if (lhs.startDate != rhs.endDate){
			return lhs.startDate < rhs.endDate;
		}
		return lhs.startTime < rhs.endTime;
	} else if (lhs.taskType == DEADLINE && rhs.taskType == NORMAL){
		if (lhs.endDate != rhs.startDate){
			return lhs.endDate < rhs.startDate;
		}
		return lhs.endTime < rhs.startTime;
	} else if (lhs.taskType == DEADLINE && rhs.taskType == DEADLINE){
		if (lhs.endDate != rhs.endDate){
			return lhs.endDate < rhs.endDate;
		}
		return lhs.endTime < rhs.endTime;
	} else if (lhs.taskType == FLOATING || rhs.taskType == FLOATING){
		return lhs.endDate < rhs.endDate;
	}
}

void Storage::sortStorage(){
	sort(activeTask.begin(), activeTask.end(), &task_sorter);
}

void Storage::writeToFile(){
	std::ofstream outputFile;
	outputFile.open(DEFAULT_DIRECTORY);
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDisplay << std::endl;
	}
	outputFile.close();	
	if (activeTask.size() >= 0){
		std::ofstream tempStorage;
	  tempStorage.open(DEFAULT_STORAGE_NAME);
	  int index;
	  if (activeTask.size() == 0){
		  tempStorage.close();
	  }else{
		  for (index = 0; index < activeTask.size() - 1; index++){
			  tempStorage << activeTask[index].taskDetails << std::endl;
			  tempStorage << to_iso_string(activeTask[index].startDate) << std::endl;
			  tempStorage << to_iso_string(activeTask[index].endDate) << std::endl;
			  tempStorage << to_iso_string(activeTask[index].startTime) << std::endl;
			  tempStorage << to_iso_string(activeTask[index].endTime) << std::endl;
			  tempStorage << activeTask[index].taskDisplay << std::endl;
			  tempStorage << activeTask[index].taskType << std::endl;
			  tempStorage << activeTask[index].specialTaskType << std::endl;
		  }
		  tempStorage << activeTask[index].taskDetails << std::endl;
		  tempStorage << to_iso_string(activeTask[index].startDate) << std::endl;
		  tempStorage << to_iso_string(activeTask[index].endDate) << std::endl;
		  tempStorage << to_iso_string(activeTask[index].startTime) << std::endl;
		  tempStorage << to_iso_string(activeTask[index].endTime) << std::endl;
		  tempStorage << activeTask[index].taskDisplay << std::endl;
		  tempStorage << activeTask[index].taskType << std::endl;
		  tempStorage << activeTask[index].specialTaskType;
		  tempStorage.close();
	      }
	  }
	if (archivedTask.size() >= 0){
		std::ofstream tempArchive;
		tempArchive.open(DEFAULT_ARCHIVE_NAME);
		int archiveIndex = 0;
		if (archivedTask.size() == 0){
			tempArchive.close();
		}else{
			for (archiveIndex = 0; archiveIndex < archivedTask.size() - 1; archiveIndex++){
				tempArchive << archivedTask[archiveIndex].taskDetails << std::endl;
				tempArchive << to_iso_string(archivedTask[archiveIndex].startDate) << std::endl;
				tempArchive << to_iso_string(archivedTask[archiveIndex].endDate) << std::endl;
				tempArchive << to_iso_string(archivedTask[archiveIndex].startTime) << std::endl;
				tempArchive << to_iso_string(archivedTask[archiveIndex].endTime) << std::endl;
				tempArchive << archivedTask[archiveIndex].taskDisplay << std::endl;
				tempArchive << archivedTask[archiveIndex].taskType << std::endl;
				tempArchive << archivedTask[archiveIndex].specialTaskType << std::endl;
			}
			tempArchive << archivedTask[archiveIndex].taskDetails << std::endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].startDate) << std::endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].endDate) << std::endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].startTime) << std::endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].endTime) << std::endl;
			tempArchive << archivedTask[archiveIndex].taskDisplay << std::endl;
			tempArchive << archivedTask[archiveIndex].taskType << std::endl;
			tempArchive << archivedTask[archiveIndex].specialTaskType;
			tempArchive.close();
		}
	}
}

std::string Storage::changeDirectory(std::string newDirectory){
#define BUFSIZE MAX_PATH
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
	if (dwRet == 0)
	{
		return MESSAGE_CURRENTDIRECTORY_FAIL;
	}
	if (dwRet > BUFSIZE)
	{
		return MESSAGE_BUFFER_SMALL;
	}
	if (!SetCurrentDirectory(newDirectory.c_str()))
	{
		return MESSAGE_SETDIRECTORY_FAIL;
	}
	writeToFile();
	return MESSAGE_SETDIRECTORY_SUCCESS + newDirectory;
}

int Storage::searchTaskDisplay(std::string thingsToSearch){
	for (int i = 0;i < activeTask.size(); i++){
		int found = thingsToSearch.find(activeTask[i].taskDisplay);
		if (found != std::string::npos){
			return i;
		}
	}
}




void Storage::deleteRecurringTask(std::vector<int> recurIndex){
	for (int i = recurIndex.size() - 1; i >= 0; i--){
		std::vector<Task>::iterator iter = activeTask.begin();
		tempTask.push(activeTask[recurIndex[i]]);
		activeTask.erase(iter + recurIndex[i]);
	}
	writeToFile();
	numberOfUndoActions.push(recurIndex.size());
}



int Storage::convertToActualIndex(int index){
	std::vector<std::string> tempTopFifteen = retrieveTopList();
	int actualTaskIndex;
	if (index <= tempTopFifteen.size()){
		actualTaskIndex = searchTaskDisplay(tempTopFifteen[index - 1]);
	}else {
		actualTaskIndex = index - 1 - tempTopFifteen.size() + retrieveNormalSize() + retrieveDeadlineSize();
	}
	return actualTaskIndex;
}



std::string Storage::deleteTask(int index){
	if (index > activeTask.size() || index <= 0){
		try{
			throw(MESSAGE_WRONG_INDEX);
		}catch (std::string wrongMsg){
			numberOfUndoActions.push(0);
			return wrongMsg;
		}
	}
	std::string tempDisplay;
	int actualTaskIndex = index-1;
	if (!lastCommandIsDisplay){
		actualTaskIndex = convertToActualIndex(index);
	}
	lastCommandIsDisplay = false;
	if (activeTask[actualTaskIndex].specialTaskType == RECUR){
		std::vector<int> recurIndex = findRecurIndex(activeTask[actualTaskIndex].taskDetails, RECUR);
		deleteRecurringTask(recurIndex);
		return MESSAGE_DELETE_RECUR;
	}else{
		std::ostringstream feedbackMessage;
		std::vector<Task>::iterator iter = activeTask.begin();
		tempDisplay = activeTask[actualTaskIndex].taskDetails;
		tempTask.push(activeTask[actualTaskIndex]);
		activeTask.erase(iter + actualTaskIndex);
		numberOfUndoActions.push(1);
		feedbackMessage << tempDisplay << " is successfully deleted.\n";
		writeToFile();
		return feedbackMessage.str();
	}
}

std::string Storage::completeTask(int index){
	if (index > activeTask.size() || index <= 0){
		numberOfUndoActions.push(0);
		return MESSAGE_WRONG_INDEX;
	}
	std::ostringstream feedbackMessage;
	std::vector<std::string> tempTopFifteen = retrieveTopList();
	std::string tempDisplay;
	int actualTaskIndex = index - 1;
	if (!lastCommandIsDisplay){
		actualTaskIndex = convertToActualIndex(index);
	}
	lastCommandIsDisplay = false;
	std::vector<Task>::iterator iter = activeTask.begin();
	tempDisplay = activeTask[actualTaskIndex].taskDetails;
	archivedTask.push_back(activeTask[actualTaskIndex]);
	activeTask.erase(iter + actualTaskIndex);
	feedbackMessage << tempDisplay << " is successfully archived.\n";
	return feedbackMessage.str();
}

void Storage::registerSearchedStuff(std::vector<Task>::iterator iter, bool& findIt, std::vector<std::string>& searchedStuff, int& count){
	tempSearchIterator.push_back(iter);
	findIt = true;
	std::ostringstream oneTask;
	oneTask << std::setfill('0') << std::setw(2) << count << ". " << iter->taskDisplay;
	searchedStuff.push_back(oneTask.str());
	count++;
}

std::vector<std::string> Storage::searchTask(std::string thingsToSearch,date dateToSearch, ptime timeToSearch ){
    colourIndex.clear();
	std::vector<std::string> searchedStuff;
	size_t found = std::string::npos;
	tempSearchIterator.clear();
	bool findIt = false;
	std::vector<Task>::iterator iter;
	int count = 1;
	bool foundAlready;
	date currentDate(day_clock::local_day());
	date tomorrowDate = currentDate + days(1);
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		std::string temp = iter->taskDisplay;
		foundAlready = false;
		if (thingsToSearch != ""){
			found = temp.find(thingsToSearch);
		}
		if (found != std::string::npos){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && dateToSearch == iter->startDate && iter->startDate != nonDate){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && dateToSearch == iter->endDate && iter->endDate != nonDate) {
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && dateToSearch == currentDate && iter->endDate != nonDate && iter->endDate == tomorrowDate){
				registerSearchedStuff(iter, findIt, searchedStuff, count);
				registerColourIndex(*iter);
				foundAlready = true;
		}
		if (!foundAlready && dateToSearch == currentDate && iter->startDate != nonDate && iter->startDate == tomorrowDate){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && timeToSearch == iter->startTime && iter->startTime != nonTime){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && timeToSearch == iter->endTime && iter->endTime != nonTime){
		    registerSearchedStuff(iter, findIt, searchedStuff, count);
		    registerColourIndex(*iter);
		    foundAlready = true;
		}	
		if (!foundAlready && iter->startDate != nonDate && dateToSearch != nonDate && dateToSearch.year() == specialDate.year() && dateToSearch.month() == iter->startDate.month()){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
		if (!foundAlready && iter->endDate != nonDate && dateToSearch != nonDate && dateToSearch.year() == specialDate.year() && dateToSearch.month() == iter->endDate.month()){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			registerColourIndex(*iter);
			foundAlready = true;
		}
	}
	return searchedStuff;
}

std::string Storage::undoAdd(){
	assert(numberOfUndoActions.size() > 0);  //assertion (defensive coding)
	int n = numberOfUndoActions.top();
	for (int i = 0; i < n; i++){
		std::string thingsToSearch = taskDetailsHistory.top();
		std::vector<Task>::iterator iter;
		for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
			std::string tempDetails = iter->taskDetails;
			if (tempDetails == thingsToSearch){
				activeTask.erase(iter);
				break;
			}
		}
		taskDetailsHistory.pop();
	}
	numberOfUndoActions.pop();
	if (n == 0){
		return MESSAGE_UNDO_EMPTY;
	}
	return MESSAGE_UNDO;
}

std::string Storage::undoDelete(){
	assert(numberOfUndoActions.size() > 0);  //assertion (defensive coding)
	int n = numberOfUndoActions.top();
	for (int i = 0; i < n; i++){
		activeTask.push_back(tempTask.top());
		tempTask.pop();
	}
	numberOfUndoActions.pop();
	sortStorage();
	if (n == 0){
		return MESSAGE_UNDO_EMPTY;
	}
	return MESSAGE_UNDO;
}

std::string Storage::undoComplete(){
	assert(numberOfUndoActions.size() > 0);  //assertion (defensive coding)
	std::string tempDisplay;
	std::ostringstream feedbackMessage;
	std::vector<Task>::iterator iter = archivedTask.begin();
	int index = archivedTask.size()-1;
	tempDisplay = archivedTask[index].taskDetails;
	activeTask.push_back(archivedTask[index]);
	archivedTask.erase(iter + index);
	return MESSAGE_UNDO;
}



std::string Storage::undoEdit(){
	if (numberOfUndoActions.top() == 0){
		return MESSAGE_UNDO_EMPTY;
	}
	numberOfUndoActions.push(numberOfUndoActions.top());
	undoAdd();
	undoDelete();
	return MESSAGE_UNDO;
}

std::string Storage::deleteSearchTask(int index){
	if (index > tempSearchIterator.size() || index <= 0){
		numberOfUndoActions.push(0);
		return MESSAGE_WRONG_INDEX;
	}
	std::ostringstream feedbackMessage;
	if (tempSearchIterator[index - 1]->specialTaskType == RECUR){
		std::vector<int> recurIndex = findRecurIndex(tempSearchIterator[index - 1]->taskDetails, RECUR);
		deleteRecurringTask(recurIndex);
		return MESSAGE_DELETE_RECUR;
	}else{
		std::string tempDisplay = (tempSearchIterator[index - 1])->taskDetails;
		tempTask.push(*tempSearchIterator[index - 1]);
		activeTask.erase(tempSearchIterator[index - 1]);
		numberOfUndoActions.push(1);
		feedbackMessage << tempDisplay << " is successfully deleted.\n";
		return feedbackMessage.str();
	}
}

std::vector<int> Storage::retrieveColourIndex(){
	return colourIndex;
}

std::string Storage::completeSearchTask(int index){
	if (index > tempSearchIterator.size() || index <= 0){
		numberOfUndoActions.push(0);
		return MESSAGE_WRONG_INDEX;
	}
	std::ostringstream feedbackMessage;
	std::string tempDisplay = (tempSearchIterator[index - 1])->taskDetails;
	archivedTask.push_back(*tempSearchIterator[index - 1]);
	activeTask.erase(tempSearchIterator[index - 1]);
	feedbackMessage << tempDisplay << " is successfully archived.\n";
	return feedbackMessage.str();
}


void Storage::updateRecurTask(Task &temporaryTask, std::string information, ptime tempStartTime, ptime tempEndTime){
	if (!information.empty()){
		temporaryTask.taskDetails = information;
	}
	if (tempStartTime != nonTime && tempStartTime != temporaryTask.startTime){
		temporaryTask.startTime = tempStartTime;
	}
	if (tempEndTime != nonTime && tempEndTime != temporaryTask.endTime){
		temporaryTask.endTime = tempEndTime;
	}
}





void Storage::updateStandardTask(Task &temporaryTask, std::string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	if (!information.empty()){
		temporaryTask.taskDetails = information;
	}
	if (tempEndDate != temporaryTask.endDate && tempEndDate != nonDate){
		if (temporaryTask.endDate == nonDate){
			temporaryTask.taskType = DEADLINE;
		}
		temporaryTask.endDate = tempEndDate;
	}
	if (tempEndTime != temporaryTask.endTime && tempEndTime != nonTime){
		if (temporaryTask.endTime == nonTime){
			temporaryTask.taskType = DEADLINE;
		}
		temporaryTask.endTime = tempEndTime;
	}
	if (tempStartTime != temporaryTask.startTime && tempStartTime != nonTime){
		if (temporaryTask.startTime == nonTime){
			temporaryTask.taskType = NORMAL;
		}
		temporaryTask.startTime = tempStartTime;
		temporaryTask.startDate = temporaryTask.endDate;
	}
	if (tempStartDate != temporaryTask.startDate && tempStartDate != nonDate){
		if (temporaryTask.startDate == nonDate){
			temporaryTask.taskType = NORMAL;
		}
		temporaryTask.startDate = tempStartDate;
	}
}

std::string Storage::editSearchTask(int index, std::string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	if (index > tempSearchIterator.size() || index <= 0){
		numberOfUndoActions.push(0);
		return MESSAGE_WRONG_INDEX;
	}
	Task temporaryTask = *tempSearchIterator[index - 1];
	if (temporaryTask.specialTaskType == RECUR && tempStartDate == nonDate && tempEndDate == nonDate){
		std::vector<int> recurIndex = findRecurIndex(temporaryTask.taskDetails, RECUR);
		for (int i = recurIndex.size()-1; i >= 0; i--){
			temporaryTask = activeTask[recurIndex[i]];
			std::vector<Task>::iterator iter = activeTask.begin();
			tempTask.push(temporaryTask);
			activeTask.erase(iter + recurIndex[i]);
			updateRecurTask(temporaryTask, information, tempStartTime, tempEndTime);
			initializeTaskDetails(temporaryTask);
			activeTask.push_back(temporaryTask);
			taskDetailsHistory.push(temporaryTask.taskDetails);
		}
		numberOfUndoActions.push(recurIndex.size());
	}else{
		temporaryTask.specialTaskType = NONRECUR;
		tempTask.push(temporaryTask);
		activeTask.erase(tempSearchIterator[index - 1]);
		updateStandardTask(temporaryTask, information, tempStartDate, tempEndDate, tempStartTime, tempEndTime);
		initializeTaskDetails(temporaryTask);
		activeTask.push_back(temporaryTask);
		numberOfUndoActions.push(1);
		taskDetailsHistory.push(temporaryTask.taskDetails);
	}
	return MESSAGE_EDIT_SUCCESS;
}



std::vector<int> Storage::findRecurIndex(std::string info, TYPE_OF_SPECIAL_TASK specialTaskType){
	std::vector<int> recurIndex;
	for (int i = 0; i < activeTask.size(); i++){
		if (info == activeTask[i].taskDetails && specialTaskType == activeTask[i].specialTaskType){
			recurIndex.push_back(i);
		}
	}
	return recurIndex;
}




std::string Storage::editTask(int index, std::string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	if (index > activeTask.size() || index <= 0){
		numberOfUndoActions.push(0);
		return MESSAGE_WRONG_INDEX;
	}
	std::ostringstream feedbackMessage;
	std::string tempDisplay;
	int actualIndex = index -1;
	if (!lastCommandIsDisplay){
		actualIndex = convertToActualIndex(index);
	}
	lastCommandIsDisplay = false;
	Task temporaryTask = activeTask[actualIndex];
	if (temporaryTask.specialTaskType == RECUR && tempStartDate == nonDate && tempEndDate == nonDate){
		std::vector<int> recurIndex = findRecurIndex(temporaryTask.taskDetails, temporaryTask.specialTaskType);
		for (int i = recurIndex.size()-1; i >= 0; i--){
			temporaryTask = activeTask[recurIndex[i]];
			std::vector<Task>::iterator iter = activeTask.begin();
			tempTask.push(activeTask[recurIndex[i]]);
			activeTask.erase(iter + recurIndex[i]);
			updateRecurTask(temporaryTask, information, tempStartTime, tempEndTime);
			initializeTaskDetails(temporaryTask);
			activeTask.push_back(temporaryTask);
			taskDetailsHistory.push(temporaryTask.taskDetails);
		}
		numberOfUndoActions.push(recurIndex.size());
	}else{
		temporaryTask.specialTaskType = NONRECUR;
		std::vector<Task>::iterator iter = activeTask.begin();
		tempTask.push(activeTask[actualIndex]);
		activeTask.erase(iter + actualIndex);
		updateStandardTask(temporaryTask, information, tempStartDate, tempEndDate, tempStartTime, tempEndTime);
		initializeTaskDetails(temporaryTask);
		activeTask.push_back(temporaryTask);
		numberOfUndoActions.push(1);
		taskDetailsHistory.push(temporaryTask.taskDetails);
	}
	return MESSAGE_EDIT_SUCCESS;
}


std::string Storage::addRecurringTask(std::string task, std::vector<date> vStartDate, std::vector<date> vEndDate, std::vector<ptime> vStartTime, std::vector<ptime> vEndTime){
	if (vStartDate.size() == 0){
		return MESSAGE_INVALID_RECUR;
	}
	//Recurring tasks can either be deadline or normal tasks
	if (vStartDate[0] == nonDate && vStartTime[0] == nonTime){
		for (int i = 0; i < vEndDate.size(); i++){
			Task temp;
			temp.taskDetails = task;
			temp.startDate = nonDate;
			temp.endDate = vEndDate[i];
			temp.startTime = nonTime;
			temp.endTime = vEndTime[i];
			temp.taskType = DEADLINE;
			temp.specialTaskType = RECUR;
			initializeTaskDetails(temp);
			taskDetailsHistory.push(task);
			activeTask.push_back(temp);
		}
	}else{
		for (int i = 0; i < vEndDate.size(); i++){
			Task temp;
			temp.taskDetails = task;
			temp.startDate = vStartDate[i];
			temp.endDate = vEndDate[i];
			temp.startTime = vStartTime[i];
			temp.endTime = vEndTime[i];
			temp.taskType = NORMAL;
			temp.specialTaskType = RECUR;
			initializeTaskDetails(temp);
			taskDetailsHistory.push(task);
			activeTask.push_back(temp);
		}	
	}
	numberOfUndoActions.push(vEndDate.size());
	sortStorage();
	writeToFile();
	return MESSAGE_RECUR_SUCCESS;
}

std::vector<std::string> Storage::reformat(std::vector<std::string> input){
	size_t position;
	size_t nextpos;
	std::vector<std::string> newOutput;
	for (int i = 0; i < input.size(); i++){
		std::ostringstream oss;
		nextpos = input[i].find("[");
		position = 0;
		if (nextpos > DEFAULT_OUTPUT_LENGTH){
			for (int j = 0; j < nextpos/DEFAULT_OUTPUT_LENGTH + 1; j++){
				if (nextpos - position <= nextpos%DEFAULT_OUTPUT_LENGTH){
					oss << std::left << std::setfill(' ') << std::setw(DEFAULT_OUTPUT_LENGTH) << input[i].substr(position, nextpos%DEFAULT_OUTPUT_LENGTH);
				}else{
					oss << input[i].substr(position, DEFAULT_OUTPUT_LENGTH) << std::endl;
				}
				position += DEFAULT_OUTPUT_LENGTH;
			}
			oss << input[i].substr(nextpos, input[i].length() - nextpos);
			newOutput.push_back(oss.str());
		}else{
			newOutput.push_back(input[i]);
		}
	}
	return newOutput;
}
