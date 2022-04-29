#pragma once

#include <string>
#include <queue>

using namespace std;

//! A class representing 1 processor.
class CPU
{
private:
	string name;

	queue<char> taskQueue;
	int cyclesToFinish = 0;				//!< Amount of processor cycles remaining until all tasks in the task queue of the CPU are processed.
	char currTask = 0;					//!< The task that's currently being processed.
	int currTaskCyclesRemaining = 0;	//!< Amount of processor cycles remaining until the current task is complete.

	unsigned int cyclesWorked = 0;
	unsigned int cyclesWorkedTotal = 0;
	string taskLog = "";

protected:
	char affinity;	//!< The affinity of the given CPU (The task that takes the least time to process on the CPU).

public:
	CPU(string name, char affinity);


	string GetName();
	char GetAffinity();
	int GetTaskCount();
	int GetCyclesToFinish();
	unsigned int GetCyclesWorked();
	unsigned int GetCyclesWorkedTotal();
	string GetTaskLog();


	/*! \brief Gets the cost of the specified task.
		\param task The task to get the cost of.
		\return The cost of the given task on the CPU.
	*/
	virtual int GetCost(char task);

	//! Adds a task to the CPU's task queue.
	void AddTask(char task);

	//! \brief Performs one CPU cycle.
	//! \return True if the CPU still has tasks to finish. False if the CPU finished all it's tasks.
	bool NextCycle();

	/*! \brief Resets the state of the CPU.
	
		Empties the task queue (if not already empty) and resets log and counters.
		Is called by the CPUSystemAbstract at the beginning of every batch.
	*/
	void Reset();
};

