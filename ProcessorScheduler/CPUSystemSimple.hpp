#pragma once

#include <queue>
#include <iostream>

#include "CPUSystemAbstract.hpp"
#include "CPU.hpp"

//! A class representing a CPUSystem with my simple scheduler.
class CPUSystemSimple : public CPUSystemAbstract
{
private:
	CPU** cpus;
	int cpuCount;

	int FindCPUWithShortestQueue();		//!< Returns the index of the CPU with the shortest queue in the cpus array.
	int FindCPUWithLongestQueue();		//!< Returns the index of the CPU with the longest queue in the cpus array.
	int FindCPUWithAffinity(char task);	//!< Returns the index of the first CPU in the cpus array that has an affinity for the given task.

protected:
	virtual void Schedule(queue<char> &tasks) override;

public:
	//! \copydoc CPUSystemAbstract::CPUSystemAbstract(CPU**, int)
	//! <br />This CPUSystem includes my simple scheduler.
	CPUSystemSimple(CPU** cpus, int cpuCount);
};

