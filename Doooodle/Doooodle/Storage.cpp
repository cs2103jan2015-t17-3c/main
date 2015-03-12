#include "Storage.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

Storage::Storage(void){
};

Storage::~Storage(void){
};

string Storage::addNormalTask(string task, date startDate, date endDate, ptime startTime, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = startDate;
	temp.endDate = endDate;
	temp.startTime = startTime;
	temp.endTime = endTime;
	activeTask.push_back(temp);
	
	History trace;
	ptime currentTime;
	currentTime = second_clock::local_time();
	//string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Normal task: " << task << " from " << startDate <<" " << startTime.time_of_day() << " to " << endDate << " " << endTime.time_of_day() << " successfully added.\n";
	return feedback.str();
};

string Storage::addDeadlineTask(string task, date date, ptime time){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = date;
	temp.startTime = time;
	temp.endTime = time;
	temp.endDate = date;
	activeTask.push_back(temp);
	
	History trace;
	ptime currentTime;
	currentTime = second_clock::local_time();
	//string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Deadline task: " << task << " at " << date << " " << time.time_of_day() << " successfully added.\n";
	return feedback.str();
};

string Storage::addFloatTask(string task){
	Task temp;
	temp.taskDetails = task;
	//temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	History trace;
	ptime currentTime;
	currentTime = second_clock::local_time();
	//string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Float task: " << task << " successfully added.\n";
	return feedback.str();
};

vector<string> Storage::retrieveTopFive(){
	vector<string> TopFive;
	for (int i = 0; i < 5; i++){
		if (i < activeTask.size()) {
			Task dummy = activeTask[i];
			ostringstream oneTask;
			if ((activeTask[i].endTime != activeTask[i].startTime) || (activeTask[i].endDate != activeTask[i].startDate)){
				oneTask << i + 1 << ". " << dummy.taskDetails << " from " << dummy.startDate << " " << dummy.startTime.time_of_day() << " to " << dummy.endDate << " " << dummy.endTime.time_of_day();
			}
			else 
				oneTask << i + 1 << ". " << dummy.taskDetails << " by " << dummy.endDate << " " << dummy.endTime.time_of_day();
			TopFive.push_back(oneTask.str());
		}
		else {
			TopFive.push_back("");
		}
	}
	return TopFive;
}

bool task_sorter(Task const& lhs, Task const& rhs){
	if (lhs.startDate != rhs.startDate)
		return lhs.startDate < rhs.startDate;
	return lhs.startTime < rhs.startTime;
}

void Storage::sortStorage(){
	sort(activeTask.begin(), activeTask.end(), &task_sorter);
}

void Storage::writeToFile(string textFileName){
	ofstream outputFile;
	outputFile.open(textFileName);
	for (int index = 0; index < activeTask.size(); index++){
		if (activeTask[index].endTime != activeTask[index].startTime || activeTask[index].endDate != activeTask[index].startDate){
			outputFile << index + 1 << ". " << activeTask[index].taskDetails << " from " << activeTask[index].startDate << " " << activeTask
				[index].startTime << " to " << activeTask[index].endDate << " " << activeTask[index].endTime;
		}
		else
			outputFile << index + 1 << ". " << activeTask[index].taskDetails << " by " << activeTask[index].startDate << " " << activeTask[index].startTime;	
			}
	outputFile.close();
	//ostringstream returnMessage;
	//returnMessage << textFileName << " is successfully saved.\n";
	//return returnMessage.str();
}

string Storage::deleteTask(int index){
	ostringstream feedbackMessage;
	vector<Task>::iterator iter = activeTask.begin();
	feedbackMessage << activeTask[index - 1].taskDetails << " is successfully deleted.\n";
	activeTask.erase(iter + index - 1);
	return feedbackMessage.str();
}

//vector<string> ususal
string Storage::searchTask(string thingsToSearch){
	vector<string> searchedStuff;
	bool findIt = false;
	vector<Task>::iterator iter;
	int count = 1;
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		string temp = iter->taskDetails;
		size_t found = temp.find(thingsToSearch);
		if (found != string::npos){
			findIt = true;
			ostringstream oneTask;
			if (iter->endTime != iter->startTime || iter->endDate != iter->startDate){
				oneTask << count << ". " << iter->taskDetails << " from " << iter->startDate << " " << iter->startTime << " to " << iter->endDate << " " << iter->endTime;
				}
				else
					oneTask << count << ". " << iter->taskDetails << " by " << iter->startDate << " " << iter-> startTime;
			searchedStuff.push_back(oneTask.str());
		}
		count++;
	}
	if (findIt){
		return "item found.";
	}
	else
		return "item is not there.";
	//return findIt;
	//return searchedStuff;
}





