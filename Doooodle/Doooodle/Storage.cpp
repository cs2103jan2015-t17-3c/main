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
		/*if (i < activeTask.size()) {
			Task dummy = activeTask[i];
			ostringstream oneTask;
			oneTask << dummy.taskDetails << " " << dummy.startTime << " " << dummy.endTime << endl;
			TopFive.push_back(oneTask.str());
		}
		else*/ {
			TopFive.push_back("");
		}
	}
	return TopFive;
}

void Storage::sortStorage(){
	int i, j;
	for (i = 0; i < activeTask.size() - 1; i++){

		for (j = i + 1; j < activeTask.size(); j++){
			if (activeTask[i].startTime.compare(activeTask[j].startTime) > 0){
				Task dummy = activeTask[i];
				activeTask[i] = activeTask[j];
				activeTask[j] = dummy;
			}

		}
	}
}






