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
  float CpuUtilization();
  std::string Command();                                                                                   
  std::string Ram();
  std::string User();                        
  long int UpTime();                      
  bool operator<(Process const& a) const;
  Process(int _pid, float _cpu, std::string _cmd, std::string _ram, std::string _user, long _upTime);


  // private members
 private:
  int pid;
  float cpuUtilization;
  std::string command;
  std::string ram;
  std::string user;
  long int upTime;
};

#endif