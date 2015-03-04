#include "Storage.h"

using namespace chrono;

Storage::Storage(void){
};

Storage::Storage(void){
};

string Storage::addNormalTask(string task, string startTime, string endTime){
	Task temp;
	temp.taskDetails = task;
	temp.startTime = startTime;
	temp.endTime = endTime;
	activeTask.push_back(temp);
	
	History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Normal task: " << task << " from " << startTime << " to " << endTime << " successfully added : )\n";
	return feedback.str();
};

string Storage::addDueTask(string task, string time){
	Task temp;
	temp.taskDetails = task;
	temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Due task: " << task << " at " << time << " successfully added : )\n";
	return feedback.str();
};

string Storage::addFloatTask(string task){
	Task temp;
	temp.taskDetails = task;
	//temp.startTime = time;
	//temp.endTime = time;
	activeTask.push_back(temp);
	
	History trace;
	time_t tt;
	tt = system_clock::to_time_t(system_clock::now());
	string currentTime = ctime(&tt);
	trace.requestTime = currentTime;
	trace.commandDetails = temp;
	commandHistory.push_back(trace);
	
	ostringstream feedback;
	feedback << "Float task: " << task << " successfully added : )\n";
	return feedback.str();
};






