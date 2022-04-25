#pragma once

#include <queue>
#include <iostream>

#include "CPUSystemAbstract.hpp"
#include "CPU.hpp"

class CPUSystemSimple : CPUSystemAbstract
{
private:
	CPU** cpus;
	int cpuCount;

	char* affinities;

	int FindCPUWithShortestQueue();
	int FindCPUWithLongestQueue();
	int FindCPUWithAffinity(char task);

protected:
	virtual void Schedule(queue<char> tasks) override;

public:
	CPUSystemSimple(CPU** cpus, int cpuCount);
	virtual ~CPUSystemSimple() override;
};

