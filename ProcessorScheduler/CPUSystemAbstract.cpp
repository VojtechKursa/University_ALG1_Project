#include "CPUSystemAbstract.hpp"

CPUSystemAbstract::CPUSystemAbstract(CPU** cpus, int cpuCount)
{
    this->cpuCount = cpuCount;
    this->cpus = new CPU*[cpuCount];

    for(int i = 0; i < cpuCount; i++)
    {
        this->cpus[i] = new CPU(*cpus[i]);
    }
}

CPUSystemAbstract::~CPUSystemAbstract()
{
    for(int i = 0; i < cpuCount; i++)
    {
        delete cpus[i];
    }

    delete[] cpus;
}



int CPUSystemAbstract::GetCyclesWorked()
{ return this->cyclesWorked; }

int CPUSystemAbstract::GetCyclesWorkedTotal()
{ return this->cyclesWorkedTotal; }

void CPUSystemAbstract::GetCPUs(CPU** &cpus, int &cpuCount)
{
    cpus = this->cpus;
    cpuCount = this->cpuCount;
}

CPU** CPUSystemAbstract::GetCPUs()
{ return this->cpus; }

int CPUSystemAbstract::GetCPUCount()
{ return this->cpuCount; }



void CPUSystemAbstract::ProcessBatch(queue<char> &tasks)
{
    if (cpuCount < 1)
    {
        std::cout << "ERR: Attempted to process a batch of tasks with no CPUs in the system." << std::endl;
        return;
    }

    Reset();

    queue<char> tasksCopy;
    while (!tasks.empty())
    {
        char task = tasks.front();
        tasks.pop();

        this->batch += task;
        tasksCopy.push(task);
    }

    Schedule(tasksCopy);

    bool run;
    do
    {
        run = false;

        for (int i = 0; i < cpuCount; i++)
        {
            run |= cpus[i]->NextCycle();
        }
    } while(run);

    cyclesWorked = FindMaxCyclesWorked();
    cyclesWorkedTotal += cyclesWorked;
}

string CPUSystemAbstract::GetBatchReport()
{
    string report = "BATCH REPORT: " + batch + "\n";

    CPU* cpu;
    for(int i = 0; i < cpuCount; i++)
    {
        cpu = cpus[i];
        report += cpu->GetName() + " worked " + to_string(cpu->GetCyclesWorked()) + " cycles:\n";
        report += "\t" + cpu->GetTaskLog() + "\n";
    }

    report += "Cycles worked this batch: " + to_string(cyclesWorked) + "\n";
    report += "Cycles worked total: " + to_string(cyclesWorkedTotal);
    
    return report;
}



void CPUSystemAbstract::Reset()
{
    for(int i = 0; i < cpuCount; i++)
    {
        cpus[i]->Reset();
    }

    cyclesWorked = 0;
    batch = "";
}

int CPUSystemAbstract::FindMaxCyclesWorked()
{
    if(cpuCount > 0)
    {
        int max = cpus[0]->GetCyclesWorked();
        
        for(int i = 1; i < cpuCount; i++)
        {
            if(cpus[i]->GetCyclesWorked() > (unsigned int)max)
                max = cpus[i]->GetCyclesWorked();
        }

        return max;
    }
    else
        return 0;
}