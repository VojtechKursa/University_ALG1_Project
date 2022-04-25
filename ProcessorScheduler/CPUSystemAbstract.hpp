#pragma once

#include <string>
#include <queue>
#include <iostream>

#include "CPU.hpp"

using namespace std;

class CPUSystemAbstract
{
private:
	CPU** cpus;
	int cpuCount;

	int cyclesWorked = 0;
	int cyclesWorkedTotal = 0;

	void Reset();
	int FindMaxCyclesWorked();

protected:
	void GetCPUs(CPU** &cpus, int &cpuCount);
	CPU** GetCPUs();
	int GetCPUCount();

	virtual void Schedule(queue<char> &tasks) = 0;

public:
	CPUSystemAbstract(CPU** cpus, int cpuCount);
	virtual ~CPUSystemAbstract();

	int GetCyclesWorked();
	int GetCyclesWorkedTotal();

	void ProcessBatch(queue<char> &tasks);

	string GetBatchReport();
};

