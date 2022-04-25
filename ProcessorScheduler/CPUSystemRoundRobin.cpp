#include "CPUSystemRoundRobin.hpp"

CPUSystemRoundRobin::CPUSystemRoundRobin(CPU** cpus, int cpuCount) : CPUSystemAbstract(cpus, cpuCount)
{ }



void CPUSystemRoundRobin::Schedule(queue<char> &tasks)
{
    CPU** cpus;
    int cpuCount;
    GetCPUs(cpus, cpuCount);

    int selectedCPU = 0;
    while(!tasks.empty())
    {
        cpus[selectedCPU]->AddTask(tasks.front());
        tasks.pop();
        
        selectedCPU = (selectedCPU + 1) % cpuCount;
    }
}