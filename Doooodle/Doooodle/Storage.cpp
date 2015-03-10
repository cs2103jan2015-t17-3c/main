#include "Storage.h"

using namespace chrono;

Storage::Storage(void){
};

Storage::~Storage(void){
};

string Storage::addNormalTask(string task, string startTime, string endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startTime = startTime;
	temp.endTime = endTime;
	activeTask.push_back(temp);
	
	/*History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);*/
	
	ostringstream feedback;
	feedback << "Normal task: " << task << " from " << startTime << " to " << endTime << " successfully added.\n";
	return feedback.str();
};

string Storage::addDeadlineTask(string task, string time){
	Task temp;
	temp.taskDetails = task;
	temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	/*History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);*/
	
	ostringstream feedback;
	feedback << "Deadline task: " << task << " at " << time << " successfully added.\n";
	return feedback.str();
};

string Storage::addFloatTask(string task){
	Task temp;
	temp.taskDetails = task;
	//temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	/*History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);*/
	
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
			if (activeTask[i].endTime != "\0"){

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
	return lhs.startTime < rhs.startTime;
}

void Storage::sortStorage(){
	sort(activeTask.begin(), activeTask.end(), &task_sorter);
}

string Storage::writeToFile(string textFileName){
	ofstream outputFile;
	outputFile.open(textFileName);
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDetails << " " << activeTask[index].startTime << " " << activeTask[index].endTime << endl;
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





