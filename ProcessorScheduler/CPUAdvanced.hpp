#pragma once

#include "CPU.hpp"
#include "TaskCost.h"

class CPUAdvanced : CPU
{
private:
	TaskCost* costs;
	int costsLength;

public:
	CPUAdvanced(string name, TaskCost* costs, int costsLength);
	virtual ~CPUAdvanced();

	virtual int GetCost(char task) override;	//Returns the cost of the specific task on the CPU
};

