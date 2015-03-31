#include "StorageDeadlineTask.h"

const date StorageDeadlineTask::nonDate(not_a_date_time);
const ptime StorageDeadlineTask::nonTime(not_a_date_time);
const int StorageDeadlineTask::DEFAULT_WIDTH = 25;

StorageDeadlineTask::StorageDeadlineTask(void){
};

StorageDeadlineTask::~StorageDeadlineTask(void){
};

string StorageDeadlineTask::initializeTaskDetails(Task temp){
	ostringstream outputTask;
		if (temp.endTime == nonTime){
			outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << setfill('0') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << "      ]";
		} else{
			outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << setfill('0') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "]";
		}
	return outputTask.str();
}

string StorageDeadlineTask::taskDetailsFeedback(Task temp){
	ostringstream outputTask;
		if (temp.endTime == nonTime){
			outputTask << "Deadline task: " << temp.taskDetails << " by " << setfill('0') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " successfully added.\n";
		}
		else{
			outputTask << "Deadline task: " << temp.taskDetails << " by " << setfill('0') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
		}
	return outputTask.str();
}

Task StorageDeadlineTask::initializeDeadlineTask(string task, date endDate, ptime endTime){
	Task temp;
	temp.taskDetails = task;
	temp.endDate = endDate;
	temp.endTime = endTime;
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

string StorageDeadlineTask::addDeadlineTask(string task, date endDate, ptime endTime){
	Task temp = initializeDeadlineTask(task, endDate, endTime);
	//taskDetailsHistory.push(task);
	activeDeadlineTask.push_back(temp);
	//commandHistory.push_back(trace);
	return taskDetailsFeedback(temp);
};

int StorageDeadlineTask::retrieveDeadlineSize(){
	return activeDeadlineTask.size();
}

bool StorageDeadlineTask::task_sorter(Task const& lhs, Task const& rhs){
	if (lhs.endDate != rhs.endDate){
		return lhs.endDate < rhs.endDate;
	}
	return lhs.endTime < rhs.endTime;
};

void StorageDeadlineTask::sortStorage(){
	sort(activeDeadlineTask.begin(), activeDeadlineTask.end(), &task_sorter);
}

string StorageDeadlineTask::deleteDeadlineTask(int index){
	ostringstream feedbackMessage;
	vector<Task>::iterator iter = activeDeadlineTask.begin();
	string tempDisplay = activeDeadlineTask[index - 1].taskDetails;
	//tempTask.push(activeTask[index - 1]);
	activeDeadlineTask.erase(iter + index - 1);
	feedbackMessage << tempDisplay << " is successfully deleted.\n";
	return feedbackMessage.str();
}

