#include "CPUAdvanced.hpp"

CPUAdvanced::CPUAdvanced(string name, TaskCost* costs, int costsLength) : CPU(name, 0)
{
	this->costsLength = costsLength;

	if (costs != nullptr && costsLength > 0)
	{
		this->costs = new TaskCost[costsLength];
		for (int i = 0; i < costsLength; i++)
		{
			this->costs[i] = costs[i];
		}

		int min = this->costs[0].cost;
		int minIndex = 0;
		for (int i = 1; i < costsLength; i++)
		{
			if (this->costs[i].cost < min)
			{
				min = this->costs[i].cost;
				minIndex = i;
			}
		}

		this->affinity = this->costs[minIndex].task;
	}
	else
	{
		this->affinity = 0;
		this->costs = nullptr;
	}
}

CPUAdvanced::~CPUAdvanced()
{
	if (this->costs != nullptr)
		delete[] this->costs;
}



int CPUAdvanced::GetCost(char task)
{
	for (int i = 0; i < costsLength; i++)
	{
		if (costs[i].task == task)
			return costs[i].cost;
	}

	return UINT16_MAX;
}