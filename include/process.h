#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                              
  std::string User();                     
  std::string Command();                  
  float CpuUtilization();                 
  std::string Ram();                       
  long int UpTime();                      
  bool operator<(Process const& a) const;
  Process(int _pid, std::string _user, std::string _cmd, std::string _ram,float _cpu,long _upTime);


  // private members
 private:
  int pid;
  std::string user;
  std::string command;
  float cpuUtilization;
  std::string ram;
  long int upTime;
};

#endif