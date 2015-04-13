//@author A0108562H
//ITASK is an Interface Class for other Logic classes such as:
//DeadlineTask, DeleteTask, EditTask, FloatingTask, NormalTask, OverdueTask, SearchTask, UndoTask

#ifndef ITASK_H_
#define ITASK_H_

#include <iostream>
#include <assert.h>
#include "Storage.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

class ITask {

public:
	virtual ~ITask(void) = 0;
	virtual std::string loadTask();

protected:
	std::string task;
	std::string displayMessage;
	date dateStart;
	date dateEnd;
	ptime timeStart;
	ptime timeEnd;

private:
	static const std::string STRING_TEMPLATE;

};

#endif