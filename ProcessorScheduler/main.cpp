#include <iostream>
#include <queue>

#include "CPU.hpp"
#include "CPUSystemAbstract.hpp"
#include "CPUSystemRoundRobin.hpp"
#include "CPUSystemSimple.hpp"
#include "TaskCost.h"
#include "CPUAdvanced.hpp"
#include "CPUSystemAdvanced.hpp"

using namespace std;

int random(int min, int max)
{
	return (rand() % (max - min)) + min;
}

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	int batchNum = 4;
	queue<char> taskBatch;

	CPU* cpus[3];
	cpus[0] = new CPU("CPU L", 'L');
	cpus[1] = new CPU("CPU M", 'M');
	cpus[2] = new CPU("CPU H", 'H');

	CPUSystemAbstract* cpuSystem = new CPUSystemSimple(cpus, 3);

	for (int i = 0; i < 3; i++)
	{
		delete cpus[i];
	}

	for (int currBatch = 0; currBatch < 4; currBatch++)
	{
		cout << "Batch " << currBatch << ": ";

		for (int i = 0; i < 8; i++)
		{
			int taskNum = random(0, 2);
			char task;

			switch (taskNum)
			{
			case 0: task = 'L'; break;
			case 1:	task = 'M'; break;
			case 2: task = 'H'; break;
			default: task = 0; break;
			}

			cout << task;
			taskBatch.push(task);
		}

		cpuSystem->ProcessBatch(taskBatch);

		cout << endl << cpuSystem->GetBatchReport() << endl << endl;
	}

	delete cpuSystem;

	return 0;
}