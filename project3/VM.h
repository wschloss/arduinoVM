// CSCI442
// Project3

#define VERBOSE 0
#define TABLE_SIZE 16
#define PAGE_SIZE 32
#define SRAM 5
#define HOLD 7

#include "SpiRAM.h"

class VM {
public:
  VM() : spiram(0,9), faults(0), refs(0) {}

  int& operator[](int address);

  // Gets the fault rate
  float getFaultRate();

  // Resets the current fault rate
  void resetFaultRate();

private:
  // Number of faults and refs
  int faults;
  int refs;
  // Virtual memory interaction
  SpiRAM spiram;

  // inverted page table (physical mem number -> page number there)
  //int invPageTable[16];
  // Page table (Page Number -> physical mem number)
  // -1 if not memory
  int pageTable[16];

  // Physical memory
  int physicalMem[TABLE_SIZE * PAGE_SIZE];

};
