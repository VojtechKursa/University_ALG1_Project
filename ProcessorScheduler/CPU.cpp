#include "CPU.hpp"

CPU::CPU(string name, char affinity)
{
	this->name = name;
	this->affinity = affinity;
}



string CPU::GetName()
{ return this->name; }

char CPU::GetAffinity()
{ return this->affinity; }

int CPU::GetTaskCount()
{ return (int)this->taskQueue.size(); }

int CPU::GetCyclesToFinish()
{ return this->cyclesToFinish; }

unsigned int CPU::GetCyclesWorked()
{ return this->cyclesWorked; }

unsigned int CPU::GetCyclesWorkedTotal()
{ return this->cyclesWorkedTotal; }

string CPU::GetTaskLog()
{ return this->taskLog; }



int CPU::GetCost(char task)
{
	return task == affinity ? 1 : 2;
}



void CPU::AddTask(char task)
{
	taskQueue.push(task);
	cyclesToFinish += GetCost(task);
}

bool CPU::NextCycle()
{
	bool newTask = false;

	if (currTaskCyclesRemaining <= 0)
	{
		if (taskQueue.empty())
		{
			return false;
		}
		else
		{
			char task = taskQueue.front();
			taskQueue.pop();

			currTaskCyclesRemaining = GetCost(task);
			currTask = task;
			newTask = true;
		}
	}

	currTaskCyclesRemaining--;
	cyclesToFinish--;
	cyclesWorked++;
	cyclesWorkedTotal++;

	if (newTask)
		taskLog += currTask;
	else
		taskLog += tolower(currTask);
	taskLog += ' ';

	return !(currTaskCyclesRemaining == 0 && taskQueue.empty());
}

void CPU::Reset()
{
	taskLog = "";
	cyclesWorked = 0;

	cyclesToFinish = 0;
	currTaskCyclesRemaining = 0;
	currTask = 0;

	while (!taskQueue.empty())
	{
		taskQueue.pop();
	}
}