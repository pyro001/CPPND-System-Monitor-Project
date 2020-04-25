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
      if (line_number == i) 
      {
        std::remove(line.begin(), line.end(), ':');
        // std::replace(line.begin(), line.end(), ' ', '_');
        std::remove(line.begin(), line.end(), '=');
        std::remove(line.begin(), line.end(), '"');

        std::remove(line.begin(), line.end(), '(');
        std::remove(line.begin(), line.end(), ')');
        std::remove(line.begin(), line.end(), '-');

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

        // std::replace(line.begin(), line.end(), ' ', '_');
        std::remove(line.begin(), line.end(), '=');
        std::remove(line.begin(), line.end(), '"');

        std::remove(line.begin(), line.end(), '(');
        std::remove(line.begin(), line.end(), ')');
        std::remove(line.begin(), line.end(), '-');
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
         // return data1;
      }

      // std::cout<<data;
    }
    // (data1={"data"});
  } 
  return data1;   
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
  long upTime = stol(uptime_system);
  return upTime;
}
//------ DEPRECATED FUNCTIONALITES: THESE ARE DONE IN PROCESSOR.CPP NOW-----
// TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// 
// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() {
//    return LinuxParser::FetchValue("/proc/stat",0) ;}
//-----------deprecated functioNALITIES END------

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function

long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return std::stoi(FetchValue("/proc/stat","processes",0).at(0)) ; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {return stoi(FetchValue("/proc/stat","procs_running",0).at(0)); }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid ) {
  //vector<string> vec=FetchValue(kProcDirectory + to_string(pid) + kCmdlineFilename,0,1);
   std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string line;
  vector<string> data1;
  string junk, data;
  if (stream.is_open()) {
  std::getline(stream, line);
     }
    return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid ) { 
   try
  {
       long mb=stol(FetchValue(kProcDirectory + to_string(pid) + kStatusFilename,"VmSize:",0).at(0))/1024;
       return to_string(mb);
 
  }
  catch(...)
  {return 0;
    
  }
 
   }

// TODO: Read and return the user ID associated with a process

string LinuxParser::Uid(int pid)
{
  auto input = FetchValue("/proc/" + to_string(pid) + "/status", "Uid:", 1);

  return input.at(1);
}
// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid)
{
  //step1. get uid
  string user_ID = Uid(pid);
  string user;

  vector<string> vec = FetchValue("/etc/passwd", (user_ID), 1);
  user= vec.at(0);
//std::copy(vec.begin(),vec.end(),std::experimental::make_ostream_joiner(std::cout,",\t"));
//auto loc=std::find(vec.begin(),vec.end(),user_ID)+1;
user = user.substr(0,user.find(':'));
return user;
}
// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid )
 {
   vector<string> vec=   LinuxParser::FetchValue(kProcDirectory + to_string(pid) + kStatFilename,0,1);
    long starttime = stol(vec.at(21))/ sysconf(_SC_CLK_TCK);
return starttime;
 }
 float LinuxParser::precessorutil(int pid)
 {
   vector<string> vec=   LinuxParser::FetchValue(kProcDirectory + to_string(pid) + kStatFilename,0,1);
   long seconds =LinuxParser::UpTime()-LinuxParser::UpTime(pid);
   float totaltime = (stof(vec.at(utimeloc))+stof(vec.at(cutimeloc))+stof(vec.at(cstimeloc)))/sysconf(_SC_CLK_TCK);
 return (100*totaltime/(seconds));
 }