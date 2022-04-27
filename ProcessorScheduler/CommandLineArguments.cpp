#include "CommandLineArguments.hpp"

CommandLineArguments::CommandLineArguments(int argc, char** argv)
{
	ProcessArguments(argc, argv);
}



void CommandLineArguments::ProcessArguments(int argc, char** argv)
{
	string currArgument;
	for (int i = 1; i < argc; i++)
	{
		currArgument = argv[i];

		if (currArgument[0] != '-')
			this->inputFile = currArgument;
		else
		{
			string flag;

			if (currArgument[1] == '-')
			{
				flag = currArgument.substr(2);
			}
			else
			{
				flag = currArgument.substr(1);
			}

			if (flag == "h" || flag == "help")
			{
				this->printHelp = true;
				return;
			}
			else if (flag == "s" || flag == "scheduler")
			{
				if (i + 1 < argc)
				{
					int temp = -1;
					
					try
					{
						temp = stoi(argv[i + 1]);
					}
					catch (exception)
					{
						cout << "WARN: Specified scheduler (" << argv[i+1] << ") is invalid, must be a number.\n";
						i++;
						continue;
					}

					if (temp >= 0 && temp <= 1)
					{
						this->selectedScheduler = (SelectedScheduler)temp;
						i++;
					}
					else
						cout << "WARN: Invalid scheduler specified (" << argv[i + 1] << ").\n";
				}
				else
					cout << "WARN: Flag scheduler found, but no scheduler specified behind.\n";
			}
			else if (flag == "o" || flag == "output")
			{
				if (i + 1 < argc)
				{
					this->outputFile = argv[i + 1];
					i++;
				}
				else
					cout << "WARN: Output file flag found, but no output file specified.\n";
			}
			else if (flag == "nc" || flag == "no-console-output")
			{
				this->allowcout = false;
			}
			else
			{
				cout << "WARN: Unrecognized flag " + flag + ".\n";
			}
		}
	}
}



string CommandLineArguments::GetInputFile()
{
	return this->inputFile;
}

string CommandLineArguments::GetOutputFile()
{
	return this->outputFile;
}

SelectedScheduler CommandLineArguments::GetSelectedScheduler()
{
	return this->selectedScheduler;
}

bool CommandLineArguments::GetAllowCOut()
{
	return this->allowcout;
}

bool CommandLineArguments::GetPrintHelp()
{
	return this->printHelp;
}