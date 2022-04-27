#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "CommandLineArguments.hpp"
#include "SelectedSchedulerEnum.h"
#include "CPU.hpp"
#include "CPUSystemAbstract.hpp"
#include "CPUSystemRoundRobin.hpp"
#include "CPUSystemSimple.hpp"
#include "TaskCost.h"
#include "CPUAdvanced.hpp"
#include "CPUSystemAdvanced.hpp"

#include "mainAuxFuncs.h"

using namespace std;

int main(int argc, char** argv)
{
	CommandLineArguments args(argc, argv);

	if (args.GetPrintHelp())
	{
		printHelp();
		exit(0);
	}

	ifstream inputFile = openInputFile(args);
	
	CPUSystemAbstract* cpuSystem = createCPUSystem(args);

	string buffer;
	getline(inputFile, buffer);
	if (inputFile.fail())
	{
		cout << "ERR: Failed to read line 1 of input file.\n";
		exit(1);
	}
	int taskCount;
	try
	{
		taskCount = stoi(buffer);
	}
	catch (exception)
	{
		cout << "ERR: First line of the input file must be a number.\n";
		exit(1);
	}

	queue<char> allTasks;

	for(int i = 0; i < taskCount; i++)
	{
		getline(inputFile, buffer);

		if (inputFile.fail() || buffer.size() < 1)
		{
			cout << "ERR: Failed to read line " << i + 1 << " of input file.\n";
			exit(1);
		}

		allTasks.push(buffer[0]);
	}

	inputFile.close();

	ofstream outputFile = openOutputFile(args);
	queue<char> taskBatch;

	while (!allTasks.empty())
	{
		int stopPoint = min(8, (int)allTasks.size());
		for (int i = 0; i < stopPoint; i++)
		{
			taskBatch.push(allTasks.front());
			allTasks.pop();
		}

		cpuSystem->ProcessBatch(taskBatch);

		if (outputFile.is_open())
			outputFile << cpuSystem->GetBatchReport() << "\n\n";
		if(args.GetAllowCOut())
			cout << cpuSystem->GetBatchReport() << "\n\n";
	}

	cout << "Simulation finished, total cycles worked: " << cpuSystem->GetCyclesWorkedTotal() << endl;

	if(outputFile.is_open())
		outputFile << "Simulation finished, total cycles worked: " << cpuSystem->GetCyclesWorkedTotal() << endl;

	outputFile.close();


	delete cpuSystem;

	return 0;
}