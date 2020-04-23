#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H
#include<vector>
#include <fstream>
#include <regex>
#include <string>
#define utimeloc 13
#define stimeloc 14
#define cutimeloc 15
#define cstimeloc 16

/*#14 utime - CPU time spent in user code, measured in clock ticks
#15 stime - CPU time spent in kernel code, measured in clock ticks
#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
#22 starttime - Time when the process started, measured in clock ticks*/
namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"}; 
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();
std::vector< std::string>  FetchValue(std::string file_location, int line_number,bool Grablable=false);
std::vector<std::string>FetchValue(std::string file_location,std::string lable123, bool Grablable);
//vector< std::string> FetchValue(string file_location, int line_number);
// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
// long Jiffies();
// long ActiveJiffies();
// long IdleJiffies();

long ActiveJiffies(int pid);

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
float precessorutil(int pid);
};  // namespace LinuxParser

#endif