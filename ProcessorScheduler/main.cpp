#include <iostream>
#include <fstream>
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

using namespace std;

void printHelp()
{
	// To do: help
}

CPUSystemAbstract* createCPUSystem(CommandLineArguments args)
{
	const int cpuCount = 3;

	CPUSystemAbstract* cpuSystem;

	CPU* cpus[cpuCount];
	cpus[0] = new CPU("Cortex-A510 (L)", 'L');
	cpus[1] = new CPU("Cortex-A710 (M)", 'M');
	cpus[2] = new CPU("Cortex-X2 (H)", 'H');

	switch (args.GetSelectedScheduler())
	{
	case SelectedScheduler::RoundRobin: cpuSystem = new CPUSystemRoundRobin(cpus, cpuCount); break;
	case SelectedScheduler::Simple:
	case SelectedScheduler::Unspecified:
	default: cpuSystem = new CPUSystemSimple(cpus, cpuCount); break;
	}

	for (int i = 0; i < 3; i++)
	{
		delete cpus[i];
		cpus[i] = nullptr;
	}

	return cpuSystem;
}

ifstream openInputFile(CommandLineArguments args)
{
	ifstream inputFile;

	if (args.GetInputFile() != "")
	{
		inputFile.open(args.GetInputFile(), ios::in);

		if (!inputFile.is_open())
		{
			cout << "ERR: Failed to open the input file " << args.GetInputFile() << ".\n";
			exit(1);
		}
	}
	else
	{
		cout << "ERR: Input file not specified.\n";
		exit(1);
	}

	return inputFile;
}

ofstream openOutputFile(CommandLineArguments args)
{
	ofstream outputFile;

	if (args.GetOutputFile() != "")
	{
		outputFile.open(args.GetOutputFile(), ios::out);

		if (!outputFile.is_open())
		{
			cout << "ERR: Failed to open the output file " << args.GetOutputFile() << ".\n";
			exit(1);
		}
	}

	return outputFile;
}

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