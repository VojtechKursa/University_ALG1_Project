#pragma once

#include <string>
#include <iostream>

#include "SelectedSchedulerEnum.h"

using namespace std;

//! Class for parsing and holding arguments passed from the command line
class CommandLineArguments
{
private:
	string inputFile = "";
	string outputFile = "";
	SelectedScheduler selectedScheduler = SelectedScheduler::Unspecified;
	bool allowcout = true;
	bool printHelp = false;

	void ProcessArguments(int argc, char** argv);

public:
	CommandLineArguments(int argc, char** argv);

	string GetInputFile();
	string GetOutputFile();
	SelectedScheduler GetSelectedScheduler();
	bool GetAllowCOut();
	bool GetPrintHelp();
};

