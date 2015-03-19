#include "Storage.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

date nonDate(not_a_date_time);
ptime nonTime(not_a_date_time);

const string Storage::MESSAGE_UNDO = "Undo is successfully performed";
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
	outputTask << left << setw(defaultWidth) << task << " from " << startDate << " " << startTime.time_of_day() << " to " << endDate << " " << endTime.time_of_day();
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
	logging(trace.commandDisplay);
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
	outputTask << left << setw(defaultWidth) << task << " by " << endDate << " " << endTime.time_of_day();
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
	logging(trace.commandDisplay);

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
	logging(trace.commandDisplay);

	return feedback.str();
};

vector<string> Storage::retrieveTopFive(){
	vector<string> TopTasks;
	int defaultWidth = 25;
	int numberOfDisplay = 5;
	for (int i = 0; i < numberOfDisplay && i < activeTask.size(); i++){
			Task dummy = activeTask[i];
			ostringstream oneTask;
			oneTask << i + 1 << ". " << dummy.taskDisplay;
		    TopTasks.push_back(oneTask.str());
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
	outputFile.open("Doooodle.txt");
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDisplay << endl;
	}
	outputFile.close();	
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
vector<string> Storage::searchTask(string thingsToSearch){
	vector<string> searchedStuff;
	tempSearchIterator.clear();
	bool findIt = false;
	vector<Task>::iterator iter;
	int count = 1;
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		string temp = iter->taskDetails;
		size_t found = temp.find(thingsToSearch);
		if (found != string::npos){
			tempSearchIterator.push_back(iter);
			findIt = true;
			ostringstream oneTask;
			oneTask << count << ". " << iter->taskDisplay << endl;		
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