#pragma once

#include <string>
#include <queue>
#include <iostream>

#include "CPU.hpp"

using namespace std;

/*! \brief Abstract class representing the base class for all CPUSystems.

	Handles standard tasks like processing a batch or generating a batch report, so child classes can focus on implementing their scheduler.
*/
class CPUSystemAbstract
{
private:
	CPU** cpus;
	int cpuCount;

	int cyclesWorked = 0;
	int cyclesWorkedTotal = 0;
	string batch = "";

	void Reset();
	int FindMaxCyclesWorked();

protected:
	//! Copies the pointer to the array of CPUs of the system as well as the length of that array into the given variables.
	void GetCPUs(CPU** &cpus, int &cpuCount);
	CPU** GetCPUs();
	int GetCPUCount();

	/*! \brief A method implementing the scheduler.
		\param tasks A queue of tasks to be distributed among the CPUs.

		A method that implements an algorithm for distributing the given tasks among the available CPUs.
	*/
	virtual void Schedule(queue<char> &tasks) = 0;

public:
	/*! \brief Creates a new instance of a CPUSystem.
		\param cpus An array of CPUs to be a part of the new system.
		\param cpuCount The number of CPUs in the cpus array.

		The cpus given to this constructor are duplicated before being assigned to the CPUSystem.
		Therefore both the cpus array and the CPUs in that array can be used or disposed of without any impact on the CPUSystem.
	*/
	CPUSystemAbstract(CPU** cpus, int cpuCount);
	virtual ~CPUSystemAbstract();

	int GetCyclesWorked();
	int GetCyclesWorkedTotal();

	/*! \brief Starts processing a new batch of tasks.
		\param tasks A queue of tasks to process.

		Resets the CPUs in the system, calls a scheduler that distributes the tasks among the available CPUs and starts processing the batch until it's finished.
	*/
	void ProcessBatch(queue<char> &tasks);

	//! Generates a report of the last processed batch based on the data provided by the CPUs.
	string GetBatchReport();
};

