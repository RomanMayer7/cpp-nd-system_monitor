#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>


#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes()
 { 
    vector<int> _pids = LinuxParser::Pids(); //GET pid's

    for(int _pid :_pids) //Populate "processes_" container
    {
        string command = LinuxParser::Command(_pid);
        string ram = LinuxParser::Ram(_pid);
        string user = LinuxParser::User(_pid);
        long upTime =LinuxParser::UpTime(_pid);
        float cpuUtilization=LinuxParser::getCPUutilization(_pid);

        Process process(_pid,user,command,ram,cpuUtilization,upTime);
        processes_.push_back(process);
    } 

    std::sort(processes_.begin(), processes_.end());

    return processes_; 
 }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel()
 { 
    return LinuxParser::Kernel();
 }

// DONE: Return the system's memory utilization
float System::MemoryUtilization()
{ 
    return LinuxParser::MemoryUtilization(); 
}

// DONE: Return the operating system name
std::string System::OperatingSystem()
 { 
    return LinuxParser::OperatingSystem();
 }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() 
 { 
    return LinuxParser::RunningProcesses();
 }
// DONE: Return the total number of processes on the system
int System::TotalProcesses()
 { 
    return LinuxParser::TotalProcesses();
 }

// DONE: Return the number of seconds since the system started running
long int System::UpTime()
 { 
      long int value = LinuxParser::UpTime();
      //std::cout<<"time:"<<Format::ElapsedTime(value)<<std::endl;
      return value;
 }