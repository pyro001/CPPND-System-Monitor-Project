#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:

  float Utilization();  // TODO: See src/processor.cpp
  private:
float idle;
float active;
float prev_idle=0;
float prev_active=0;
};

#endif