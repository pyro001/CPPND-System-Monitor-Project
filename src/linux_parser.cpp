#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <ostream>
#include <string>
#include <vector>
#define debug false
using std::stof;
using std::string;
using std::to_string;
using std::vector;
// get value from lines as a function
std::vector<std::string> LinuxParser::FetchValue(string file_location,
                                                 int line_number,
                                                 bool Grablable) {
  std::ifstream stream(file_location);
  string line;
  vector<string> data1;
  string junk, data;
  if (stream.is_open()) {
    for (int i = 0; i <= line_number; i++) {
      std::getline(stream, line);
      if (line_number == i) {
        std::istringstream memline1(line);
        memline1 >> junk >> data;
        if (Grablable == true) data1.emplace_back(junk);
        data1.emplace_back(data);
        while (memline1 >> data) {
          data1.emplace_back(data);
        }
        // std::cout<<data;
      }
    }
  }

  return data1;
}
std::vector<string>LinuxParser::FetchValue(string file_location,string lable, bool Grablable) {
    std::ifstream stream(file_location);
  string line;
  vector<string> data1;
  string labledata, data;
  if (stream.is_open()) {
    while (std::getline(stream, line)) 
    {
      std::istringstream memline1(line);
      memline1 >> labledata >> data;
     // cout<<"\nlable data" <<labledata;
      if ((labledata.find(lable)+1)>0 ) {
        //  cout<<"lable match \n\n";
        if (Grablable == true) data1.emplace_back(labledata);
        data1.emplace_back(data);
        while (memline1 >> data) {
          data1.emplace_back(data);
        }
          return data1;
      }

      // std::cout<<data;
    }
    return (data1={"data"});
  }    
}

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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  // grab the line 1 in the /proc/meminfo
  string line;
  float mem_util;
  // get the variable you want to grab
  // string junk,MemTotal,MemFree;// junk is just ignroable data
  // isolate the values, prototype : MemTotal:       16275688 kB
  float MemTotal =
      stof((FetchValue(kProcDirectory + kMeminfoFilename, 0).at(0)));
  // isolate the values, prototype :MemFree:         8940436 kB
  float MemFree = stof(
      (LinuxParser::FetchValue(kProcDirectory + kMeminfoFilename, 1)).at(0));
  mem_util = (MemTotal - MemFree) / MemTotal;
  return mem_util;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime_system;

  uptime_system = FetchValue(kProcDirectory + kUptimeFilename, 0, true).at(0);
  long upTime = stof(uptime_system);
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() {
//    return LinuxParser::FetchValue("/proc/stat",0) ;}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return std::stoi(FetchValue("/proc/stat","processes",0).at(0)) ; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {return stoi(FetchValue("/proc/stat","procs_running",0).at(0)); }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }