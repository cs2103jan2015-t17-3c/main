#include "Storage.h"

date nonDate(not_a_date_time);
ptime nonTime(not_a_date_time);

const string Storage::MESSAGE_UNDO = "Undo is successfully performed";
const string Storage::DEFAULT_DIRECTORY = "dooodle.txt";
const int Storage::DEFAULT_WIDTH = 25;
const int Storage::NUMBER_OF_DISPLAY = 10;
const int Storage::NUMBER_OF_FLOAT_DISPLAY = 5;

Storage::Storage(void){
};

Storage::~Storage(void){
};

string Storage::initializeTaskDetails(Task temp){
	ostringstream outputTask;
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " from " << temp.startDate << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate << " " << setfill('0') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setw(2) << temp.endTime.time_of_day().minutes();
				} else{
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " from " << temp.startDate << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate;
				}
			} else{
				if (temp.endTime != nonTime){
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " from " << temp.startDate << " to " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes();
				} else{
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " from " << temp.startDate << " to " << temp.endDate;
				}
			}
		} else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " from " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes();
			}
		}
	} else if (temp.taskType == DEADLINE){
			if (temp.endTime == nonTime){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " by " << temp.endDate;
			} else{
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " by " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes();
			}
		} else if (temp.taskType == FLOAT){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails;
			}
	return outputTask.str();
}

string Storage::taskDetailsFeedback(Task temp){
	ostringstream outputTask;
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " from " << temp.startDate << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate << " " << setfill('0') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
				} else{
					outputTask << "Normal task: " << temp.taskDetails << " from " << temp.startDate << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate << " successfully added.\n";
				}
			} else{
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " from " << temp.startDate << " to " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
				} else{
					outputTask << "Normal task: " << temp.taskDetails << " from " << temp.startDate << " to " << temp.endDate << " successfully added.\n";
				}
			}
		} else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				outputTask << "Normal task: " << temp.taskDetails << " from " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << " to " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
			}
		}
	} else if (temp.taskType == DEADLINE){
		if (temp.endTime == nonTime){
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate << " successfully added.\n";

		} else{
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
		}
	} else if(temp.taskType == FLOAT){
		outputTask << "Float task: " << temp.taskDetails << " successfully added.\n";
	}
	return outputTask.str();
}

Task Storage::initializeNormalTask(string task, date startDate, date endDate, ptime startTime, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = startDate;
	temp.endDate = endDate;
	temp.startTime = startTime;
	temp.endTime = endTime;
	temp.taskType = NORMAL;
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

History Storage::registerHistory(Task temp){
	History trace;
	ptime currentTime;
	currentTime = second_clock::local_time();
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	ostringstream addCommandDisplay;
	addCommandDisplay << temp.taskDisplay << " " << currentTime << endl;
	trace.commandDisplay = addCommandDisplay.str();
	return trace;
}

string Storage::addNormalTask(string task, date startDate, date endDate, ptime startTime, ptime endTime){
	Task temp = initializeNormalTask(task, startDate, endDate, startTime, endTime);
	taskDetailsHistory.push(task);
	//for undo etc..
	activeTask.push_back(temp);
	History trace = registerHistory(temp) ;
	commandHistory.push_back(trace);
	return taskDetailsFeedback(temp);
};

Task Storage::initializeDeadlineTask(string task, date endDate, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = endDate;
	temp.startTime = nonTime;
	temp.endTime = endTime;
	temp.taskType = DEADLINE;
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

string Storage::addDeadlineTask(string task, date endDate, ptime endTime){
	Task temp = initializeDeadlineTask(task,endDate,endTime);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
    return taskDetailsFeedback(temp);
};

Task Storage::initializeFloatTask(string task){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = nonDate;
	temp.startTime = nonTime;
	temp.endTime = nonTime;
	temp.taskType = FLOAT;
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

string Storage::addFloatTask(string task){
	Task temp = initializeFloatTask(task);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
	return taskDetailsFeedback(temp);
};

vector<string> Storage::retrieveTopTen(){
	vector<string> TopTasks;
	for (int i = 0; i < NUMBER_OF_DISPLAY && i < activeTask.size(); i++){
		Task dummy = activeTask[i];
		if (dummy.taskType != FLOAT){
			ostringstream oneTask;
			oneTask << i + 1 << ". " << dummy.taskDisplay;
			TopTasks.push_back(oneTask.str());
		}
		} 	
	return TopTasks;
}

vector<string> Storage::retrieveFloatingTask(){
	vector<string> TopTasks;
	int count = 0;
	for (int i = 0; i < activeTask.size() && count < NUMBER_OF_FLOAT_DISPLAY; i++){
		if (activeTask[i].taskType == FLOAT){
			TopTasks.push_back(activeTask[i].taskDisplay);
			count++;
		}
	}
	return TopTasks;
}

bool task_sorter(Task const& lhs, Task const& rhs){
	if (lhs.taskType == NORMAL && rhs.taskType == NORMAL){
		if (lhs.startDate != rhs.startDate)
			return lhs.startDate < rhs.startDate;
		return lhs.startTime < rhs.startTime;
	} else if (lhs.taskType == NORMAL && rhs.taskType == DEADLINE){
		if (lhs.startDate != rhs.endDate)
			return lhs.startDate < rhs.endDate;
		return lhs.startTime < rhs.endTime;
	} else if (lhs.taskType == DEADLINE && rhs.taskType == NORMAL){
		if (lhs.endDate != rhs.startDate)
			return lhs.endDate < rhs.startDate;
		return lhs.endTime < rhs.startTime;
	} else if (lhs.taskType == DEADLINE && rhs.taskType == DEADLINE){
		if (lhs.endDate != rhs.endDate)
			return lhs.endDate < rhs.endDate;
		return lhs.endTime < rhs.endTime;
	} else if (lhs.taskType == FLOAT || rhs.taskType == FLOAT)
		return lhs.endDate < rhs.endDate;
}

void Storage::sortStorage(){
	sort(activeTask.begin(), activeTask.end(), &task_sorter);
}

void Storage::writeToFile(){
	ofstream outputFile;
	outputFile.open(directoryName);
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDisplay << endl;
	}
	outputFile.close();	
}

void Storage::changeDirectory(string newDirectory){
	directoryName = newDirectory + DEFAULT_DIRECTORY;
	return;
}

string Storage::deleteTask(int index){
	ostringstream feedbackMessage;
	vector<Task>::iterator iter = activeTask.begin();
	string tempDisplay = activeTask[index - 1].taskDetails;
	tempTask.push(activeTask[index - 1]);
	activeTask.erase(iter + index - 1);
	feedbackMessage << tempDisplay << " is successfully deleted.\n";
	return feedbackMessage.str();
}

void Storage::registerSearchedStuff(vector<Task>::iterator iter, bool& findIt, vector<string>& searchedStuff,int& count){
	tempSearchIterator.push_back(iter);
	findIt = true;
	ostringstream oneTask;
	oneTask << count << ". " << iter->taskDisplay;
	searchedStuff.push_back(oneTask.str());
	count++;
}

vector<string> Storage::searchTask(string thingsToSearch,date dateToSearch, ptime timeToSearch ){
	vector<string> searchedStuff;
	size_t found = string::npos;
	tempSearchIterator.clear();
	bool findIt = false;
	vector<Task>::iterator iter;
	int count = 1;
	bool foundAlready;
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		string temp = iter->taskDisplay;
		foundAlready = false;
		if (thingsToSearch != ""){
			found = temp.find(thingsToSearch);
		}
		if (found != string::npos){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}
		if (dateToSearch == iter->startDate && iter->startDate != nonDate && !foundAlready){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}
		if	(dateToSearch == iter->endDate && iter->endDate != nonDate && !foundAlready) {
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}
		if (timeToSearch == iter->startTime && iter->startTime != nonTime && !foundAlready){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}
		if (timeToSearch == iter->endTime && iter->endTime != nonTime && !foundAlready){
		registerSearchedStuff(iter, findIt, searchedStuff, count);
		foundAlready = true;
		
		}	
	}
	if (findIt){
		return searchedStuff;
	}
	else {
		searchedStuff.push_back("Item is not there\n");
		return searchedStuff;
	}	
}

string Storage::undoAdd(){
	string thingsToSearch = taskDetailsHistory.top();
	vector<Task>::iterator iter;
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		string temp = iter->taskDetails;
		if (temp == thingsToSearch){
			activeTask.erase(iter);
			break;
		}
	}
	taskDetailsHistory.pop();
	return MESSAGE_UNDO;
}

string Storage::undoDelete(){
	activeTask.push_back(tempTask.top());
	tempTask.pop();
	sortStorage();
	return MESSAGE_UNDO;
}

string Storage::undoEdit(){
	undoAdd();
	undoDelete();
	return MESSAGE_UNDO;
}

string Storage::deleteSearchTask(int index){
	ostringstream feedbackMessage;
	string tempDisplay = (tempSearchIterator[index-1])->taskDetails;
	tempTask.push(*tempSearchIterator[index - 1]);
	activeTask.erase(tempSearchIterator[index - 1]);
	feedbackMessage << tempDisplay << " is successfully deleted.\n";
	return feedbackMessage.str();
}

string Storage::editSearchTask(int index, string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	Task temporaryTask = *tempSearchIterator[index - 1];
	deleteSearchTask(index);
	if (!information.empty()){
		temporaryTask.taskDetails = information;
	}
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
	temporaryTask.taskDisplay = initializeTaskDetails(temporaryTask);
	activeTask.push_back(temporaryTask);
	taskDetailsHistory.push(temporaryTask.taskDetails);
	return "task is successfuly edited";
}

string Storage::editTask(int index, string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	ostringstream feedbackMessage;
	Task temporaryTask = activeTask[index - 1];
	vector<Task>::iterator iter = activeTask.begin();
	activeTask.erase(iter + index - 1);
	if (!information.empty()){
		temporaryTask.taskDetails = information;
	}
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
	temporaryTask.taskDisplay = initializeTaskDetails(temporaryTask);
	activeTask.push_back(temporaryTask);
	taskDetailsHistory.push(temporaryTask.taskDetails);
	return "Task is successfuly edited";
}