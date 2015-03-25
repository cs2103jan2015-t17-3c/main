#include "Storage.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

date nonDate(not_a_date_time);
ptime nonTime(not_a_date_time);

const string Storage::MESSAGE_UNDO = "Undo is successfully performed";
const string Storage::DEFAULT_DIRECTORY = "dooodle.txt";
Storage::Storage(void){
};

Storage::~Storage(void){
};

Task initializeNormalTask(string task, date startDate, date endDate, ptime startTime, ptime endTime){
	int defaultWidth = 25;
	Task temp;
	
	temp.taskDetails = task;
	temp.startDate = startDate;
	temp.endDate = endDate;
	temp.startTime = startTime;
	temp.endTime = endTime;
	temp.taskType = NORMAL;
	ostringstream outputTask;
	if (startDate != nonDate){
		if (startTime != nonTime){
			if (endTime != nonTime){
				outputTask << left << setw(defaultWidth) << task << " from " << startDate << " " << startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << startTime.time_of_day().minutes() << " to " << endDate << " " << setfill('0') << setw(2) << endTime.time_of_day().hours() << ":" << setw(2) << endTime.time_of_day().minutes();
			} else{
				outputTask << left << setw(defaultWidth) << task << " from " << startDate << " " << startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << startTime.time_of_day().minutes() << " to " << endDate;
			}
		} else{
			if (endTime != nonTime){
				outputTask << left << setw(defaultWidth) << task << " from " << startDate << " to " << endDate << " " << endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << endTime.time_of_day().minutes();
			} else{
				outputTask << left << setw(defaultWidth) << task << " from " << startDate << " to " << endDate;
			}
		}
	} else{
		if (startTime != nonTime && endTime != nonTime){
			outputTask << left << setw(defaultWidth) << task << " from " << startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << startTime.time_of_day().minutes() << " to " << endDate << " " << endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << endTime.time_of_day().minutes();
		}
	}
    //outputTask << left << setw(defaultWidth) << task << " from " << startDate << " " << startTime.time_of_day().hours() << ":" << setw(2) << startTime.time_of_day().minutes() << " to " << endDate << " " << endTime.time_of_day().hours() << ":" << setw(2) << endTime.time_of_day().minutes();
	temp.taskDisplay = outputTask.str();
	return temp;
}

History registerHistory(Task temp){
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
	activeTask.push_back(temp);
	History trace = registerHistory(temp) ;
	commandHistory.push_back(trace);
	ostringstream feedback;
	feedback << "Normal task: " << temp.taskDisplay << " successfully added.\n";
//	logging(trace.commandDisplay);
	return feedback.str();
};

Task initializeDeadlineTask(string task, date endDate, ptime endTime){
	int defaultWidth = 25;
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = endDate;
	temp.startTime = nonTime;
	temp.endTime = endTime;
	temp.taskType = DEADLINE;
	ostringstream outputTask;
	if (endTime == nonTime){
		outputTask << left << setw(defaultWidth) << task << " by " << endDate;

	} else{
		outputTask << left << setw(defaultWidth) << task << " by " << endDate << " " << endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << endTime.time_of_day().minutes();
	}
	temp.taskDisplay = outputTask.str();

	return temp;
}

string Storage::addDeadlineTask(string task, date endDate, ptime endTime){
	Task temp = initializeDeadlineTask(task,endDate,endTime);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
	ostringstream feedback;
	feedback << "Deadline task: " << temp.taskDisplay << " successfully added.\n";
//	logging(trace.commandDisplay);

	return feedback.str();
};

Task initializeFloatTask(string task){
	int defaultWidth = 25;
	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = nonDate;
	temp.startTime = nonTime;
	temp.endTime = nonTime;
	temp.taskType = FLOAT;
	ostringstream outputTask;
	outputTask << left << setw(defaultWidth) << task;
	temp.taskDisplay = outputTask.str();
	
	return temp;
}

string Storage::addFloatTask(string task){
	Task temp = initializeFloatTask(task);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
	ostringstream feedback;
	feedback << "Float task: " << temp.taskDisplay << " successfully added.\n";
//	logging(trace.commandDisplay);

	return feedback.str();
};

vector<string> Storage::retrieveTopTen(){
	vector<string> TopTasks;
	int defaultWidth = 25;
	int numberOfDisplay = 10;
	for (int i = 0; i < numberOfDisplay && i < activeTask.size(); i++){
			
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
	int numberOfDisplay = 5;
	int count = 0;
	for (int i = 0; i < activeTask.size() && count < 5; i++){
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
	}else if (lhs.taskType == NORMAL && rhs.taskType == DEADLINE){
		if (lhs.startDate != rhs.endDate)
			return lhs.startDate < rhs.endDate;
		return lhs.startTime < rhs.endTime;
	}else if (lhs.taskType == DEADLINE && rhs.taskType == NORMAL){
		if (lhs.endDate != rhs.startDate)
			return lhs.endDate < rhs.startDate;
		return lhs.endTime < rhs.startTime;
	}else if (lhs.taskType == DEADLINE && rhs.taskType == DEADLINE){
		if (lhs.endDate != rhs.endDate)
			return lhs.endDate < rhs.endDate;
		return lhs.endTime < rhs.endTime;
	}else if (lhs.taskType == FLOAT || rhs.taskType == FLOAT)
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

//vector<string> ususal
vector<string> Storage::searchTask(string thingsToSearch,date dateToSearch, ptime timeToSearch ){
	vector<string> searchedStuff;
	size_t found = string::npos;
	tempSearchIterator.clear();
	bool findIt = false;
	vector<Task>::iterator iter;
	int count = 1;
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		
		string temp = iter->taskDisplay;
		if (thingsToSearch != ""){
			found = temp.find(thingsToSearch);
		}
		if (found != string::npos || (dateToSearch == iter->startDate && iter->startDate != nonDate) || (dateToSearch == iter->endDate && iter->endDate != nonDate) || (timeToSearch == iter->startTime && iter->startTime != nonTime) || (timeToSearch == iter->endTime && iter->endTime != nonTime)){
			tempSearchIterator.push_back(iter);
			findIt = true;
			ostringstream oneTask;
			oneTask << count << ". " << iter->taskDisplay;		
			searchedStuff.push_back(oneTask.str());
			count++;
		}
	}
	if (findIt){
		return searchedStuff;
	}
	else {
		searchedStuff.push_back("Item is not there\n");
		return searchedStuff;
	}	//return findIt;
	//return searchedStuff;
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

void logging(string actionDetails){
	ofstream myfile;
myfile.open("actionLog.txt");
myfile << actionDetails;
myfile.close();
}

string Storage::editTask(int index, string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
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
	activeTask.push_back(temporaryTask);
	taskDetailsHistory.push(temporaryTask.taskDetails);
	return "successfuly edited";
}