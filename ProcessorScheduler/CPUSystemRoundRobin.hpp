#pragma once

#include <queue>
#include <iostream>

#include "CPUSystemAbstract.hpp"
#include "CPU.hpp"

//! A class representing a CPUSystem with the Round Robin scheduler.
class CPUSystemRoundRobin : public CPUSystemAbstract
{
protected:
	virtual void Schedule(queue<char> &tasks) override;

public:
	//! \copydoc CPUSystemAbstract::CPUSystemAbstract(CPU**, int)
	//! <br />This CPUSystem includes the Round Robin scheduler.
	CPUSystemRoundRobin(CPU** cpus, int cpuCount);
};

