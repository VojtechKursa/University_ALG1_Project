#include "mainAuxFuncs.h"

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