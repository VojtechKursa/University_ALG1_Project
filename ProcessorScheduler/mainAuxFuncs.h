#pragma once

#include <iostream>
#include <fstream>

#include "CommandLineArguments.hpp"
#include "CPU.hpp"
#include "CPUSystemAbstract.hpp"
#include "CPUSystemRoundRobin.hpp"
#include "CPUSystemSimple.hpp"

void printHelp();
CPUSystemAbstract* createCPUSystem(CommandLineArguments args);
ifstream openInputFile(CommandLineArguments args);
ofstream openOutputFile(CommandLineArguments args);