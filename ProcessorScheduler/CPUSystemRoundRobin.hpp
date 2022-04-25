#pragma once

#include <queue>
#include <iostream>

#include "CPUSystemAbstract.hpp"
#include "CPU.hpp"

class CPUSystemRoundRobin : public CPUSystemAbstract
{
protected:
	virtual void Schedule(queue<char> &tasks) override;

public:
	CPUSystemRoundRobin(CPU** cpus, int cpuCount);
};

