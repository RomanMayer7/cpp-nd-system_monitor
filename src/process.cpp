#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization; }

// Return the command that generated this process
string Process::Command() { return command; }

// Return this process's memory utilization
string Process::Ram() { return ram; }

// Return the user (name) that generated this process
string Process::User() { return user; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return upTime; }

// DONE: Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const 
{
    return (cpuUtilization > a.cpuUtilization);
}
Process::Process(int _pid, float _cpu, std::string _cmd, std::string _ram, std::string _user, long _upTime):
pid(_pid), cpuUtilization(_cpu) ,command(_cmd), ram(_ram), user(_user) , upTime(_upTime)
{
    
}