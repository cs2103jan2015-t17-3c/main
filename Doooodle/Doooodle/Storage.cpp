#include "Storage.h"

date nonDate(not_a_date_time);
ptime nonTime(not_a_date_time);

const std::string Storage::MESSAGE_UNDO = "Undo is successfully performed";
const std::string Storage::DEFAULT_DIRECTORY = "dooodle.txt";
const int Storage::DEFAULT_WIDTH = 25;
const int Storage::NUMBER_OF_DISPLAY = 10;
const int Storage::NUMBER_OF_FLOATING_DISPLAY = 12;
const int Storage::NUMBER_OF_ARCHIVED_DISPLAY = 20;

Storage::Storage(void){
	using namespace std;

	loadTasks("tempStorage.txt", activeTask);
	loadTasks("tempArchive.txt", archivedTask);



}
	
	
	

	void Storage::loadTasks(std::string filename, std::vector<Task>& target ){
		using namespace std;
	ifstream fl_h; //file handle
	fl_h.open(filename);
	if (fl_h.good()){
		int num = 1;
		Task tempTask;
		string dummy;
		while (!fl_h.eof()){
			getline(fl_h, tempTask.taskDetails);

			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				date d(from_undelimited_string(dummy));
				tempTask.startDate = d;
			}
			else
				tempTask.startDate = nonDate;

			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				date dd(from_undelimited_string(dummy));
				tempTask.endDate = dd;
			}
			else
				tempTask.endDate = nonDate;
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				ptime t(from_iso_string(dummy));
				tempTask.startTime = t;
			}
			else
				tempTask.startTime = nonTime;
			getline(fl_h, dummy);
			if (dummy != "not-a-date-time"){
				ptime tt(from_iso_string(dummy));
				tempTask.endTime = tt;
			}
			else
				tempTask.endTime = nonTime;
			getline(fl_h, tempTask.taskDisplay);
			getline(fl_h, dummy);
			if (dummy == "0"){
				tempTask.taskType = DEADLINE;
			}
			else if (dummy == "1"){
				tempTask.taskType = FLOATING;
			}
			else
				tempTask.taskType = NORMAL;
			target.push_back(tempTask);
			//num++;
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

std::string Storage::initializeTaskDetails(Task temp){
	using namespace std;

	ostringstream outputTask;
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << setfill(' ') << setw(2) << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << setfill(' ') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "]";
				} else{
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.startDate.day() << " " << temp.startDate.month() << " " << setfill(' ') << setw(2) << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << setfill(' ') << setw(6) << "]";
				}
			} else{
				if (temp.endTime != nonTime){
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.startDate.day() << " " << temp.startDate.month() << setfill(' ') << setw(9) << "]-[" << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << setfill(' ') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "]";
				} else{
					outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.startDate.day() << " " << temp.startDate.month() << "      ]-["  << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << "      ]";
				}
			}
		} else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [      " << right << setfill(' ') << setw(2) << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << setfill(' ') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "]";
			}
		}
	} else if (temp.taskType == DEADLINE){
			if (temp.endTime == nonTime){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << "      ]";
			} else{
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails << " [" << right << setfill(' ') << setw(2) << temp.endDate.day() << " " << temp.endDate.month() << " " << setfill(' ') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "]";
			}
		} else if (temp.taskType == FLOATING){
				outputTask << left << setw(DEFAULT_WIDTH) << temp.taskDetails;
			}
	return outputTask.str();
}

std::string Storage::taskDetailsFeedback(Task temp){
	using namespace std;

	ostringstream outputTask;
	if (temp.taskType == NORMAL){
		if (temp.startDate != nonDate){
			if (temp.startTime != nonTime){
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << setfill('0') << setw(2) << temp.endTime.time_of_day().hours() << ":" << setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
				} else{
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << " " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << "      ] successfully added.\n";
				}
			} else{
				if (temp.endTime != nonTime){
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << "      ]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
				} else{
					outputTask << "Normal task: " << temp.taskDetails << " [" << temp.startDate.day() << " " << temp.startDate.month() << "      ]-[" << temp.endDate.day() << " " << temp.endDate.month() << "      ] successfully added.\n";
				}
			}
		} else{
			if (temp.startTime != nonTime && temp.endTime != nonTime){
				outputTask << "Normal task: " << temp.taskDetails << " [      " << temp.startTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.startTime.time_of_day().minutes() << "]-[" << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << "] successfully added.\n";
			}
		}
	} else if (temp.taskType == DEADLINE){
		if (temp.endTime == nonTime){
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate.day() << " " << temp.endDate.month() << " successfully added.\n";

		} else{
			outputTask << "Deadline task: " << temp.taskDetails << " by " << temp.endDate.day() << " " << temp.endDate.month() << " " << temp.endTime.time_of_day().hours() << ":" << setfill('0') << setw(2) << temp.endTime.time_of_day().minutes() << " successfully added.\n";
		}
	} else if(temp.taskType == FLOATING){
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
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

History Storage::registerHistory(Task temp){
	using namespace std;

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

std::string Storage::addNormalTask(std::string task, date startDate, date endDate, ptime startTime, ptime endTime){
	using namespace std;

	Task temp = initializeNormalTask(task, startDate, endDate, startTime, endTime);
	taskDetailsHistory.push(task);
	//for undo etc..
	activeTask.push_back(temp);
	History trace = registerHistory(temp) ;
	commandHistory.push_back(trace);
	return taskDetailsFeedback(temp);
};

Task Storage::initializeDeadlineTask(std::string task, date endDate, ptime endTime){
	using namespace std;

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

std::string Storage::addDeadlineTask(std::string task, date endDate, ptime endTime){
	using namespace std;

	Task temp = initializeDeadlineTask(task,endDate,endTime);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
    return taskDetailsFeedback(temp);
};

Task Storage::initializeFloatingTask(std::string task){
	using namespace std;

	Task temp;
	temp.taskDetails = task;
	temp.startDate = nonDate;
	temp.endDate = nonDate;
	temp.startTime = nonTime;
	temp.endTime = nonTime;
	temp.taskType = FLOATING;
	temp.taskDisplay = initializeTaskDetails(temp);
	return temp;
}

std::string Storage::addFloatingTask(std::string task){
	using namespace std;

	Task temp = initializeFloatingTask(task);
	taskDetailsHistory.push(task);
	activeTask.push_back(temp);
	History trace = registerHistory(temp);
	commandHistory.push_back(trace);
	return taskDetailsFeedback(temp);
};

std::vector<std::string> Storage::retrieveTopFifteen(){
	using namespace std;
	vector<int> sortedTaskIndex;
	vector<string> topTasks;
	int i;
	int count = 0;
	for (i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == DEADLINE){
			sortedTaskIndex.push_back(i);
			count++;
		}
		if (count == 3){
			break;
		}
	}
	for (i = 0; i < activeTask.size(); i++){
		if (activeTask[i].taskType == NORMAL){
			sortedTaskIndex.push_back(i);
			count++;
		}
		if (count == 5){
			break;
		}
	}
	for (i = 0; i < activeTask.size(); i++){
		bool repeat=false;
		for (int j = 0; j < sortedTaskIndex.size(); j++){
			if ((i == sortedTaskIndex[j] && activeTask[i].taskType != FLOATING) || activeTask[i].taskType == FLOATING){
				repeat = true;
			}
		}
		if (!repeat && sortedTaskIndex.size()!=0){
			sortedTaskIndex.push_back(i);
			count++;
		}
		if (count == 15){
			break;
		}
	}
	for (int j = 0; j < sortedTaskIndex.size(); j++){
		ostringstream oneTask;
		oneTask << setfill('0') << setw(2) << j + 1 << ". " << activeTask[sortedTaskIndex[j]].taskDisplay;
		topTasks.push_back(oneTask.str());
	}
		return topTasks;
	
}

std::vector<std::string> Storage::retrieveOverdue(){
	
	using namespace std;
	vector<string> displayOverdueTasks;
	tempOverdueTaskIterator.clear();
	vector<Task>::iterator iter;
	date d(day_clock::local_day());
	ptime t(second_clock::local_time());
	for (iter = activeTask.begin(); iter != activeTask.end(); iter++){
		if (iter->endDate < d){
			displayOverdueTasks.push_back(iter->taskDisplay);
			tempOverdueTaskIterator.push_back(iter);
		} else if (iter->endDate == d && iter->endTime < t){
				displayOverdueTasks.push_back(iter->taskDisplay);
				tempOverdueTaskIterator.push_back(iter);
		}
	}
	return displayOverdueTasks;
}

//new 3
std::string Storage::completeAll(){
using namespace std;

int index;
	for (index = 0; index < tempOverdueTaskIterator.size(); index++){
		archivedTask.push_back(*tempOverdueTaskIterator[index]);
		activeTask.erase(tempOverdueTaskIterator[index]);
	}
	return "all overdue tasks completed";
}

//new 4
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
	temporaryTask.taskDisplay = initializeTaskDetails(temporaryTask);
	activeTask.push_back(temporaryTask);
	//taskDetailsHistory.push(temporaryTask.taskDetails);
	return "task is successfuly rescheduled";
}


//new 5
std::vector<std::string> Storage::retrieveCategoricalTask(std::string typeTask){
	using namespace std;

	vector<string> displayedTasks;
	if (typeTask == "normal"){
		for (int i = 0; i < activeTask.size(); i++){
			if (activeTask[i].taskType == NORMAL){
				ostringstream oneTask;
				oneTask << setfill('0') << setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
				displayedTasks.push_back(oneTask.str());
			}
		}
			return displayedTasks;
	}
		if (typeTask == "floating"){
			for (int i = 0; i < activeTask.size(); i++){
				if (activeTask[i].taskType == FLOATING){
					ostringstream oneTask;
					oneTask << setfill('0') << setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
					displayedTasks.push_back(oneTask.str());

				}
			}
			return displayedTasks;
		}
		if (typeTask == "deadline"){
			for (int i = 0; i < activeTask.size(); i++){
				if (activeTask[i].taskType == DEADLINE){
					ostringstream oneTask;
					oneTask << setfill('0') << setw(2) << i + 1 << ". " << activeTask[i].taskDisplay;
					displayedTasks.push_back(oneTask.str());
				}
			}
			return displayedTasks;
		}
		if (typeTask == "archive"){
			for (int i = 0; i < archivedTask.size() && i < NUMBER_OF_ARCHIVED_DISPLAY; i++){
				ostringstream oneTask;
				oneTask << i + 1 << ". " << archivedTask[i].taskDisplay;
				displayedTasks.push_back(oneTask.str());
			}
			return displayedTasks;
		}
}

std::vector<std::string> Storage::retrieveFloatingTask(){
	using namespace std;
	vector<string> TopTasks;
	int count = 0;
	int displayIndex = min(11, 1+retrieveCategoricalTask("deadline").size() + retrieveCategoricalTask("normal").size());
	for (int i = 0; i < activeTask.size() && count < NUMBER_OF_FLOATING_DISPLAY; i++){
		if (activeTask[i].taskType == FLOATING){
			ostringstream floatingTaskDisplay;
			floatingTaskDisplay << setfill('0') << setw(2) << displayIndex << ". " << activeTask[i].taskDisplay;
			TopTasks.push_back(floatingTaskDisplay.str());
			count++;
			displayIndex++;
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
	} else if (lhs.taskType == FLOATING || rhs.taskType == FLOATING)
		return lhs.endDate < rhs.endDate;
}

void Storage::sortStorage(){
	sort(activeTask.begin(), activeTask.end(), &task_sorter);
}

void Storage::writeToFile(){
	using namespace std;
	ofstream outputFile;
	outputFile.open("doooodle.txt");
	for (int index = 0; index < activeTask.size(); index++){
		outputFile << index + 1 << ". " << activeTask[index].taskDisplay << endl;
	}
	outputFile.close();	
	
	ofstream tempStorage;
	tempStorage.open("tempStorage.txt"/*, /*ios::in | ios::out | ios::binary*/);
	int index;
	for (index = 0; index < activeTask.size()-1; index++){
		tempStorage << activeTask[index].taskDetails << endl;
		tempStorage << to_iso_string(activeTask[index].startDate) << endl;
		tempStorage << to_iso_string(activeTask[index].endDate) << endl;
		tempStorage << to_iso_string(activeTask[index].startTime) << endl;
		tempStorage << to_iso_string(activeTask[index].endTime) << endl;
		tempStorage << activeTask[index].taskDisplay << endl;
		tempStorage << activeTask[index].taskType << endl;
	}
	tempStorage << activeTask[index].taskDetails << endl;
	tempStorage << to_iso_string(activeTask[index].startDate) << endl;
	tempStorage << to_iso_string(activeTask[index].endDate) << endl;
	tempStorage << to_iso_string(activeTask[index].startTime) << endl;
	tempStorage << to_iso_string(activeTask[index].endTime) << endl;
	tempStorage << activeTask[index].taskDisplay << endl;
	tempStorage << activeTask[index].taskType;
	tempStorage.close();

	if (archivedTask.size() != 0){
		ofstream tempArchive;
		tempArchive.open("tempArchive.txt"/*, /*ios::in | ios::out | ios::binary*/);
		int archiveIndex = 0;
		for (archiveIndex = 0; archiveIndex < archivedTask.size() - 1; archiveIndex++){

			//cout << archivedTask.size();
			tempArchive << archivedTask[archiveIndex].taskDetails << endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].startDate) << endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].endDate) << endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].startTime) << endl;
			tempArchive << to_iso_string(archivedTask[archiveIndex].endTime) << endl;
			tempArchive << archivedTask[archiveIndex].taskDisplay << endl;
			tempArchive << archivedTask[archiveIndex].taskType << endl;
		}
		tempArchive << archivedTask[archiveIndex].taskDetails << endl;
		tempArchive << to_iso_string(archivedTask[archiveIndex].startDate) << endl;
		tempArchive << to_iso_string(archivedTask[archiveIndex].endDate) << endl;
		tempArchive << to_iso_string(archivedTask[archiveIndex].startTime) << endl;
		tempArchive << to_iso_string(archivedTask[archiveIndex].endTime) << endl;
		tempArchive << archivedTask[archiveIndex].taskDisplay << endl;
		tempArchive << archivedTask[archiveIndex].taskType;
		tempArchive.close();
	}

}

void Storage::changeDirectory(std::string newDirectory){
	using namespace std;

#define BUFSIZE MAX_PATH
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(BUFSIZE, Buffer);

	if (dwRet == 0)
	{
		printf("GetCurrentDirectory failed (%d)\n", GetLastError());
		return;
	}
	if (dwRet > BUFSIZE)
	{
		printf("Buffer too small; need %d characters\n", dwRet);
		return;
	}

	if (!SetCurrentDirectory(newDirectory.c_str()))
	{
		printf("SetCurrentDirectory failed (%d)\n", GetLastError());
		return;
	}
	_tprintf(TEXT("Set current directory to %s\n"), newDirectory);
	return;
}

int Storage::searchTaskDisplay(std::string thingsToSearch){
	//bool foundAlready = false;
	using namespace std;

	for (int i = 0;/* !foundAlready &&*/ i < activeTask.size(); i++){
		int found = thingsToSearch.find(activeTask[i].taskDisplay);
		if (found != string::npos){
			return i;
		}
	}
}

std::string Storage::deleteTask(int index){
	using namespace std;

	ostringstream feedbackMessage;
	vector<string> tempTopFifteen = retrieveTopFifteen();
	string tempDisplay;
	int tempSearchTaskIndex;
	if (index < tempTopFifteen.size()){
		 tempSearchTaskIndex = searchTaskDisplay(tempTopFifteen[index - 1]);
	}
	else {
		tempSearchTaskIndex = index - 1 - tempTopFifteen.size() + retrieveCategoricalTask("deadline").size() + retrieveCategoricalTask("normal").size();
	}
		vector<Task>::iterator iter = activeTask.begin();
		tempDisplay = activeTask[tempSearchTaskIndex].taskDetails;
		tempTask.push(activeTask[tempSearchTaskIndex]);
		activeTask.erase(iter + tempSearchTaskIndex);
	feedbackMessage << tempDisplay << " is successfully deleted.\n";
	return feedbackMessage.str();
}

std::string Storage::completeTask(int index){
	using namespace std;

	ostringstream feedbackMessage;
	vector<string> tempTopFifteen = retrieveTopFifteen();
	string tempDisplay;
	int tempSearchTaskIndex;
	if (index < tempTopFifteen.size()){
		tempSearchTaskIndex = searchTaskDisplay(tempTopFifteen[index - 1]);
	}
	else {
		tempSearchTaskIndex = index - 1 - tempTopFifteen.size() + retrieveCategoricalTask("deadline").size() + retrieveCategoricalTask("normal").size();
	}

	vector<Task>::iterator iter = activeTask.begin();
    tempDisplay = activeTask[tempSearchTaskIndex].taskDetails;
	archivedTask.push_back(activeTask[tempSearchTaskIndex]);
	activeTask.erase(iter + tempSearchTaskIndex);
	feedbackMessage << tempDisplay << " is successfully archived.\n";
	return feedbackMessage.str();
}

void Storage::registerSearchedStuff(std::vector<Task>::iterator iter, bool& findIt, std::vector<std::string>& searchedStuff,int& count){
	using namespace std;

	tempSearchIterator.push_back(iter);
	findIt = true;
	ostringstream oneTask;
	oneTask << count << ". " << iter->taskDisplay;
	searchedStuff.push_back(oneTask.str());
	count++;
}

std::vector<std::string> Storage::searchTask(std::string thingsToSearch,date dateToSearch, ptime timeToSearch ){
using namespace std;

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
		if (dateToSearch.year() == 1900 && dateToSearch.month() == iter->startDate.month() && !foundAlready){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}
		if (dateToSearch.year() == 1900 && dateToSearch.month() == iter->endDate.month() && !foundAlready){
			registerSearchedStuff(iter, findIt, searchedStuff, count);
			foundAlready = true;
		}

//change

	}
	if (findIt){
		return searchedStuff;
	}
	else {
		searchedStuff.push_back("Item is not there\n");
		return searchedStuff;
	}	
}

std::string Storage::undoAdd(){
	using namespace std;

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

std::string Storage::undoDelete(){
	using namespace std;

	activeTask.push_back(tempTask.top());
	tempTask.pop();
	sortStorage();
	return MESSAGE_UNDO;
}

std::string Storage::undoEdit(){
	undoAdd();
	undoDelete();
	return MESSAGE_UNDO;
}

std::string Storage::deleteSearchTask(int index){
	
	using namespace std;

	ostringstream feedbackMessage;
	string tempDisplay = (tempSearchIterator[index-1])->taskDetails;
	tempTask.push(*tempSearchIterator[index - 1]);
	activeTask.erase(tempSearchIterator[index - 1]);
	feedbackMessage << tempDisplay << " is successfully deleted.\n";
	return feedbackMessage.str();
}

std::string Storage::completeSearchTask(int index){
	using namespace std;
	ostringstream feedbackMessage;
	string tempDisplay = (tempSearchIterator[index - 1])->taskDetails;
	archivedTask.push_back(*tempSearchIterator[index - 1]);
	activeTask.erase(tempSearchIterator[index - 1]);
	feedbackMessage << tempDisplay << " is successfully archived.\n";
	return feedbackMessage.str();
}

std::string Storage::editSearchTask(int index, std::string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	using namespace std;
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

std::string Storage::editTask(int index, std::string information, date tempStartDate, date tempEndDate, ptime tempStartTime, ptime tempEndTime){
	using namespace std;
	ostringstream feedbackMessage;
	vector<string> tempTopFifteen = retrieveTopFifteen();
	string tempDisplay;
	int tempSearchTaskIndex;
	if (index < tempTopFifteen	.size()){
		tempSearchTaskIndex = searchTaskDisplay(tempTopFifteen[index - 1]);
	}
	else {
		tempSearchTaskIndex = index - 1 - tempTopFifteen.size() + retrieveCategoricalTask("deadline").size() + retrieveCategoricalTask("normal").size();
	}
	Task temporaryTask = activeTask[tempSearchTaskIndex];
	vector<Task>::iterator iter = activeTask.begin();
	activeTask.erase(iter + tempSearchTaskIndex);
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

	temporaryTask.taskDisplay = initializeTaskDetails(temporaryTask);
	activeTask.push_back(temporaryTask);
	taskDetailsHistory.push(temporaryTask.taskDetails);
	return "Task is successfuly edited";
}


std::string Storage::addRecurringTask(std::string task, std::vector<date> vStartDate, std::vector<date> vEndDate, std::vector<ptime> vStartTime, std::vector<ptime> vEndTime){
	using namespace std;
	if (vStartDate[0] == nonDate && vStartTime[0] == nonTime){
		for (int i = 0; i < vEndDate.size(); i++){
			addDeadlineTask(task, vEndDate[i], vEndTime[i]);
		}
	}
	else{
		for (int i = 0; i < vEndDate.size(); i++){
			addNormalTask(task,vStartDate[i],vEndDate[i], vStartTime[i], vEndTime[i]);
		}
	}
	sortStorage();
	writeToFile();
	return "Recurring Task is successfully added!";
}


