#pragma once

#include <string>
#include <queue>

using namespace std;

class CPU
{
private:
	string name;

	queue<char> taskQueue;
	int cyclesToFinish = 0;
	char currTask = 0;
	int currTaskCyclesRemaining = 0;	//Amount of processor cycles remaining until the currently processed task is complete

	unsigned int cyclesWorked = 0;
	unsigned int cyclesWorkedTotal = 0;
	string taskLog = "";

protected:
	char affinity;

public:
	CPU(string name, char affinity);

	string GetName();
	char GetAffinity();
	int GetTaskCount();
	int GetCyclesToFinish();
	unsigned int GetCyclesWorked();
	unsigned int GetCyclesWorkedTotal();
	string GetTaskLog();

	virtual int GetCost(char task);	//Returns the cost of the specific task on the CPU

	void AddTask(char task);
	bool NextCycle();
	void Reset();
};

