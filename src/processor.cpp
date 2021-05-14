#include "processor.h"
#include <chrono>
#include <thread>
#include "linux_parser.h"
#include <iostream>



// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
 { 
    std::string firstCPUrecord,secondCPUrecord;
    int Idle,NonIdle,Total,PrevIdle,PrevNonIdle,PrevTotal;
    
    std::string currentLine,user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;

    std::string previousLine,prevuser,prevnice,prevsystem,previdle,previowait,previrq,prevsoftirq,
    prevsteal,prevguest,prevguest_nice; 

    //----------------------------------------------------------------------------------------------------------
    firstCPUrecord=LinuxParser::GetCPURecord();

    std::istringstream linestream_(firstCPUrecord);
    linestream_ >> previousLine>>prevuser>>prevnice>>prevsystem>>previdle>>previowait>>previrq>>prevsoftirq>>
    prevsteal>>prevguest>>prevguest_nice;

    
    //Sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    secondCPUrecord=LinuxParser::GetCPURecord();

    std::istringstream linestream(secondCPUrecord);
    linestream >> currentLine>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal>>guest>>guest_nice;


    //-----------------------------------------------------------------------------------------------------------
    PrevIdle=(std::stoi(previdle) + std::stoi(previowait));
    Idle=(std::stoi(idle) + std::stoi(iowait));

    PrevNonIdle=(std::stoi(prevuser) + std::stoi(prevnice) + std::stoi(prevsystem) + std::stoi(previrq) +
     std::stoi(prevsoftirq) + std::stoi(prevsteal));
    NonIdle=(std::stoi(user) + std::stoi(nice) + std::stoi(system) + std::stoi(irq) + std::stoi(softirq) + std::stoi(steal));

    PrevTotal=(PrevIdle + PrevNonIdle);
    Total=(Idle + NonIdle);

    float totald=(Total - PrevTotal);
    // std::cout<<"totald:"<<totald<<std::endl;
    float idled=(Idle - PrevIdle);
    //std::cout<<"idled:"<<idled<<std::endl;

    float CPU_Percentage=((totald - idled)/totald);

    return CPU_Percentage; 

 }

