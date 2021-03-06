//@author A0108562H
//UndoTask deals with undoing of tasks

#ifndef UNDOTASK_H_
#define UNDOTASK_H_

#include <iostream>
#include "ITask.h"
#include "CommandDetails.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

class UndoTask : public ITask {

public:
	UndoTask(void);
	~UndoTask(void);
	std::string loadTask(std::vector<CommandDetails*>&, Storage&);

private:
	enum TASK_TYPE {
		ADD, ERASE, EDIT, COMPLETE, NIL
	};
	static const std::string STRING_ADD;
	static const std::string STRING_COMPLETE;
	static const std::string STRING_DELETE;
	static const std::string STRING_EDIT;
	static const std::string STRING_UNDO_FAILURE;

	TASK_TYPE retrieveTaskTypeToUndo(std::vector<CommandDetails*>&);
	std::string executeUndoAdd(std::vector<CommandDetails*>&, Storage&);
	std::string executeUndoComplete(std::vector<CommandDetails*>&, Storage&);
	std::string executeUndoDelete(std::vector<CommandDetails*>&, Storage&);
	std::string executeUndoEdit(std::vector<CommandDetails*>&, Storage&);
};

#endif