#pragma once

#include <queue>

#include "CPU.hpp"

class CPUSystemAbstract
{
protected:
	CPU** cpus;

	virtual void Schedule(queue<char> tasks) = 0;

public:
	CPUSystemAbstract(CPU** cpus);
	virtual ~CPUSystemAbstract();

	void ProcessBatch(queue<char> tasks);
};

