#include <dirent.h>
//In order to convert from "clock ticks" to seconds
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>

// Tokenizing a string using stringstream
#include <bits/stdc++.h>


#include "linux_parser.h"
#include "utils.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  float Total = stof(findValueByKey(kProcDirectory,kMeminfoFilename,filterMemTotalString));// "/proc/memInfo"
  float Free = stof(findValueByKey(kProcDirectory,kMeminfoFilename,filterMemFreeString));
  return (Total - Free) / Total;
}

// DONE: Read and return the system uptime

long LinuxParser::UpTime() 
{
  // proc/uptime
  return stol(getValueOfFile(kProcDirectory,kUptimeFilename));

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }


// DONE: Read and return the total number of processes
//find value of "processes" from "proc/meminfo"
int LinuxParser::TotalProcesses()
 { 
  int _total_processes;

    try
    {
      _total_processes = stoi(findValueByKey(kProcDirectory,kMeminfoFilename,filterProcesses));
    }
   catch(std::invalid_argument& e)
    {
      _total_processes=0;
    }
    return _total_processes;
  
 }


// DONE:  Read and return the number of running processes
//find value of "procs_running" from "proc/stat"
int LinuxParser::RunningProcesses()
 {
    int _running_processes;
    try
    {
      _running_processes = stoi(findValueByKey(kProcDirectory,kStatFilename,filterRunningProcesses));
    }
   catch(std::invalid_argument& e)
    {
      _running_processes=0;
    }
    return _running_processes;
 }


// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid)
 { 
    //get value of "/proc/{pid}/cmdline"
    return getValueOfFile(kProcDirectory + to_string(pid),kCmdlineFilename);

 }


// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid)
 {
    int _VmData;
    //Using value of "VmData" to get exact physical memory being used (as a part of Physical RAM). 
    //instead of using  "VmSize" which gives us memory usage more than our actual Physical RAM size.
    try 
    {
       _VmData =stoi(findValueByKey(kProcDirectory + to_string(pid),kStatusFilename,filterProcMem));
    }
    catch(std::invalid_argument& e)
    {
       // if no conversion could be performed
       _VmData=0;
    }

    return to_string(_VmData/1024);

  }     



// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid)
 {

   return  findValueByKey(kProcDirectory + to_string(pid),kStatusFilename,filterUID);

 }


// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid)
 {
      string line;


     string value="user";
     std::ifstream filestream(kPasswordPath);
     if (filestream.is_open())
     {
       while (std::getline(filestream, line)) 
       {    
            // Vector of string to save tokens
            vector <string> tokens;
            string intermediate;
            // stringstream class check1
             std::stringstream check1(line);
        
            // Tokenizing  ':'
           while(getline(check1, intermediate, ':'))
          {
              tokens.push_back(intermediate);
          }
          //Get UID for the Process
          string uid=LinuxParser::Uid(pid);
          //Get associated User
          if(tokens.at(2) == uid)
          { 
             //std::cout<<"MATCH:"<<std::endl; 
             return tokens.at(0);
          }
       }  

     }
     return  value;
 }

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid)
 {
      string line;
      std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
     if (filestream.is_open())
     {
           std::getline(filestream, line);
          
            // Vector of string to save tokens
            vector <string> tokens;
            string intermediate;
            // stringstream class check1
             std::stringstream check1(line);
        
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' '))
             {
              tokens.push_back(intermediate);
             }

              // "(22) starttime  %llu" value from tokens -time the process started after system boot
              //in order to get the unit of time it has been running since start you need to subtract it from the UpTime() of the system
              //before substracting we need to divide this "clock ticks" value by sysconf(_SC_CLK_TCK) to get proper units
              int upTimePid = UpTime() - stol(tokens.at(21))/sysconf(_SC_CLK_TCK);

              return upTimePid;    
       }  
        return  0;
     }
     
 
 string LinuxParser::GetCPURecord()
 {

  string line;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open())
   {
       std::getline(filestream, line); //get the first line 

   }
     return  line;
     return getValueOfFile(kProcDirectory,kStatFilename);
 }

 //GET CPU Utilization for specific Process
 float LinuxParser::getCPUutilization(int pid)
 {
     string line;
     float  cpu_usage;
     std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
     if (filestream.is_open())
     {
           std::getline(filestream, line);
          
            // Vector of string to save tokens
            vector <string> tokens;
            string intermediate;
            // stringstream class check1
             std::stringstream check1(line);
        
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' '))
             {
              tokens.push_back(intermediate);
             }
             
             //System Uptime
             long uptime=LinuxParser::UpTime();

             // C function call may also be used to return the hertz value.
             int Hertz =sysconf(_SC_CLK_TCK);
            

             //#14 utime - CPU time spent in user code, measured in clock ticks
             int utime = std::stoi(tokens.at(13));
             //#15 stime - CPU time spent in kernel code, measured in clock ticks
             int stime = std::stoi(tokens.at(14));
             //#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
              int cutime = std::stoi(tokens.at(15));
             //#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
             int cstime = std::stoi(tokens.at(16));
             //#22 starttime - Time when the process started, measured in clock ticks
             int starttime = std::stoi(tokens.at(21));
             
             
             //Calculation ************************************************************************

             //First we determine the total time spent for the process:
              float total_time = utime + stime;
              /*We also  include the time from children processes.
                we add those values to total_time:*/
               total_time = total_time + cutime + cstime;

              // Next we get the total elapsed time in seconds since the process started:
              float seconds = uptime - (starttime / Hertz);
              // std::cout<<"seconds:"<<seconds<<std::endl;

              //Finally we calculate the CPU usage percentage:
               cpu_usage = ((total_time / Hertz) / seconds);

              //*********************************************************************************
                
       }  
       return  cpu_usage;   
     }
