#include "mainAuxFuncs.h"

void printHelp()
{
	cout << "Processor scheduler simulator" << "\n";
	cout << "Usage: [exe_name] [options] [input_file]" << "\n\n";
	cout << "Available options:" << "\n";
	cout << "-h --help\t\t\tPrints this help and exits." << "\n";
	cout << "-o --output-file [filename]\tWrites output of the program into the specified file." << "\n";
	cout << "\t\t\t\tErrors and warnings are not written." << "\n";
	cout << "-s --scheduler [number]\t\tSelects the scheduler the program should use." << "\n";
	cout << "\t\t\t\tAvailable schedulers are (Round robin - 0, Simple - 1)." << "\n";
	cout << "\t\t\t\tDefaults to: Simple - 1" << "\n";
	cout << "-nc --no-console-output\t\tDisables the output to the console/terminal." << "\n";
	cout << "\t\t\t\tErrors, warnings and the final message will still be written." << "\n";
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