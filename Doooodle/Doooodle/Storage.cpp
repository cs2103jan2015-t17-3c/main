#include "Storage.h"

using namespace boost;


Storage::Storage(void){
};

Storage::~Storage(void){
};

string Storage::addNormalTask(string task, gregorian::date startDate, gregorian::date endDate, posix_time::ptime startTime, posix_time::ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = startDate;
	temp.endDate = endDate;
	temp.startTime = startTime;
	temp.endTime = endTime;
	activeTask.push_back(temp);
	
	History trace;
	posix_time::ptime currentTime;
	currentTime = posix_time::second_clock::local_time();
	//string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Normal task: " << task << " from " << startDate <<" " << startTime << " to " << endDate << " " << endTime << " successfully added.\n";
	return feedback.str();
};

string Storage::addDeadlineTask(string task, gregorian::date date, posix_time::ptime time){
	Task temp;
	temp.taskDetails = task;
	temp.startDate = date;
	temp.startTime = time;
	temp.endTime = time;
	temp.endDate = date;
	activeTask.push_back(temp);
	
	History trace;
	posix_time::ptime currentTime;
	currentTime = posix_time::second_clock::local_time();
	//string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Deadline task: " << task << " at " << date << " " << time << " successfully added.\n";
	return feedback.str();
};

string Storage::addFloatTask(string task){
	Task temp;
	temp.taskDetails = task;
	//temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	History trace;
	posix_time::ptime currentTime;
	currentTime = posix_time::second_clock::local_time();
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
			if (activeTask[i].endTime != activeTask[i].startTime || activeTask[i].endDate != activeTask[i].startDate){

				oneTask << i + 1 << ". " << dummy.taskDetails << " from " << dummy.startTime << " to " << dummy.endTime;

			}
			else
				oneTask << i + 1 << ". " << dummy.taskDetails << " by " << dummy.startTime;
				
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

string Storage::writeToFile(string textFileName){
	ofstream outputFile;
	outputFile.open(textFileName);
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDetails << " " << activeTask[index].startDate << " " <<activeTask[index].startTime<< activeTask[index].endDate << activeTask[index].endTime << endl;
	}
	outputFile.close();
	ostringstream returnMessage;
	returnMessage << textFileName << " is successfully saved.\n";
	return returnMessage.str();
}

string Storage::deleteTask(int index){
	vector<Task>::iterator iter;
	activeTask.erase(iter + index - 1);
	ostringstream feedbackMessage;
	feedbackMessage << (iter + index - 1)->taskDetails << " is successfully deleted.\n";
	return feedbackMessage.str();
}

vector<string> Storage::searchTask(string thingsToSearch){
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
	return searchedStuff;
}





