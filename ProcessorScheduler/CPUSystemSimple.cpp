#include "CPUSystemSimple.hpp"

CPUSystemSimple::CPUSystemSimple(CPU** cpus, int cpuCount) : CPUSystemAbstract(cpus, cpuCount)
{
    GetCPUs(this->cpus, this->cpuCount);

    for(int i = 0; i < this->cpuCount; i++)
    {
        this->affinities[i] = this->cpus[i]->GetAffinity();
    }
}

CPUSystemSimple::~CPUSystemSimple()
{
    delete[] affinities;
}



void CPUSystemSimple::Schedule(queue<char> tasks)
{
    CPU** cpus;
    int cpuCount;
    GetCPUs(cpus, cpuCount);

    int cpuWithAffinity;
    char currTask;

    // Phase 1 - Assign to the CPU with affinity

    int phase1Stop = tasks.size() / 2;
    for(int i = 0; i < phase1Stop; i++)
    {
        currTask = tasks.front();
        tasks.pop();

        cpuWithAffinity = FindCPUWithAffinity(currTask);
        
        if(cpuWithAffinity >= 0)
            cpus[cpuWithAffinity]->AddTask(currTask);
        else
            cpus[FindCPUWithShortestQueue()]->AddTask(currTask);
    }

    // Phase 2 - Balancing 

    int maxCyclesCPU = FindCPUWithLongestQueue();
    int maxCycles = cpus[maxCyclesCPU]->GetCyclesToFinish();
    
    while(!tasks.empty())
    {
        currTask = tasks.front();
        tasks.pop();

        cpuWithAffinity = FindCPUWithAffinity(currTask);

        if(cpuWithAffinity >= 0)
        {
            CPU* selectedCPU = cpus[cpuWithAffinity];
            
            if(selectedCPU->GetCyclesToFinish() + selectedCPU->GetCost(currTask) <= maxCycles)
            {
                selectedCPU->AddTask(currTask);
            }
            else
            {
                CPU* cpuWithLeastCycles = cpus[FindCPUWithShortestQueue()];
                if(cpuWithLeastCycles->GetCyclesToFinish() + cpuWithLeastCycles->GetCost(currTask) <= maxCycles)
                {
                    cpuWithLeastCycles->AddTask(currTask);
                }
                else
                {
                    selectedCPU->AddTask(currTask);
                    
                    maxCyclesCPU = cpuWithAffinity;
                    maxCycles = selectedCPU->GetCyclesToFinish();
                }
            }
        }
        else
        {
            cpus[FindCPUWithShortestQueue()]->AddTask(currTask);
            
            maxCyclesCPU = FindCPUWithLongestQueue();
            maxCycles = cpus[maxCyclesCPU]->GetCyclesToFinish();
        }
    }
}



int CPUSystemSimple::FindCPUWithShortestQueue()
{
    int min = cpus[0]->GetCyclesToFinish();
    int minCPU = 0;

    for(int i = 1; i < cpuCount; i++)
    {
        if(cpus[i]->GetCyclesToFinish() < min)
        {
            min = cpus[i]->GetCyclesToFinish();
            minCPU = i;
        }
    }

    return minCPU;
}

int CPUSystemSimple::FindCPUWithLongestQueue()
{
    int max = cpus[0]->GetCyclesToFinish();
    int maxCPU = 0;

    for(int i = 1; i < cpuCount; i++)
    {
        if(cpus[i]->GetCyclesToFinish() > max)
        {
            max = cpus[i]->GetCyclesToFinish();
            maxCPU = i;
        }
    }

    return maxCPU;
}

int CPUSystemSimple::FindCPUWithAffinity(char task)
{
    for(int i = 0; i < cpuCount; i++)
    {
        if(cpus[i]->GetAffinity() == task)
            return i;
    }

    return -1;
}