#include "processor.h"
#include"linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
 {
    std::vector<std::string> procstat;

procstat=LinuxParser::FetchValue("/proc/stat",0);
// Idle = idle + iowait
float idle,active,prev_idle,prev_active;
// NonIdle = user + nice + system + irq + softirq + steal
idle=stof(procstat.at(LinuxParser::kIdle_))+stof(procstat.at(LinuxParser::kIOwait_));
active=stof(procstat.at(LinuxParser::kUser_))+stof(procstat.at(LinuxParser::kNice_))+stof(procstat.at(LinuxParser::kSystem_))+stof(procstat.at(LinuxParser::kIRQ_))+stof(procstat.at(LinuxParser::kSoftIRQ_))+stof(procstat.at(LinuxParser::kSteal_));
float CPU_Percentage=active/(active+idle);
// Total = Idle + NonIdle
// # differentiate: actual value minus the previous one
// float CPU_Percentage=std::abs((active-prev_active)/((active-prev_active)+(idle-prev_idle)));
// // CPU_Percentage = (totald - idled)/totald
// prev_idle=idle;
// prev_active=active;
    return CPU_Percentage; }