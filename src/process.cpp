#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid) {pid_=pid;}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()const {   
    try
    {
        /* code */
    
    std::string line;
    float cpu_usage;

  long upTime = LinuxParser::UpTime();
  
    int utime = 0.0;
    int stime = 0.0;
    int cutime = 0.0;
    int cstime = 0.0;

    //#22
    float starttime = 0.0;

    const int pid = pid_;
    std::string pidStr = std::to_string(pid);
   auto vec=LinuxParser::FetchValue((LinuxParser:: kProcDirectory + pidStr+ LinuxParser::kStatFilename),0,1);
   
            utime = std::stoi(vec.at(utimeloc));
            stime = std::stoi(vec.at(stimeloc));
            cutime = std::stoi(vec.at(cutimeloc));
            cstime= std::stoi(vec.at(cstimeloc));
            starttime = std::stof(vec.at(starttimeloc));

            cpu_usage = ((((utime + stime+ cutime + cstime)) / sysconf(_SC_CLK_TCK)) / (upTime - starttime / sysconf(_SC_CLK_TCK)));
        
    
    return cpu_usage; 
    
    }
    catch(...)
    {
        return 10000.0;
    }}

// TODO: Return the command that generated this process
string Process::Command() { 
    try
    {
     
    return LinuxParser::Command(this->Pid());   /* code */
    }
    catch(...)
    {
       return "NA";
    } }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    try
    {
        return LinuxParser::Ram(this->Pid());
        /* code */
    }
    catch(...)
    {
       return "NA";
    }
    
     }

// TODO: Return the user (name) that generated this process
string Process::User() {  
    try
    {
        return LinuxParser::User(this->Pid());
        /* code */
    }
    catch(...)
    {
       return "NA";
    }
     }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    
    try
    {
    return LinuxParser::UpTime(this->Pid());    /* code */
    }
    catch(...)
    {
       return 00;
    }
     }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return (this->CpuUtilization()>a.CpuUtilization()); }