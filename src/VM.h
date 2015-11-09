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
  VM() : spiram(0,9), faults(0), refs(0) {
    //for (int i = 0; i < 1024; i++) {
    //    pageTable[i] = -1;
    //}
    for (int i = 0; i < 16; i++) {
        invPageTable[i] = i;
    }
  }

  int& operator[](unsigned int address);

  int getLastPageOut(){return lastPageOut;};
  int getLastAddressIn(){return lastAddressIn;};
  
  // Gets the fault rate
  
  float getFaultRate();

  // Resets the current fault rate
  void resetFaultRate();

private:
  // Number of faults and refs
  unsigned long faults;
  unsigned long refs;
  int nextPage = 0;
  int lastPageOut = 0;
  int lastAddressIn = 0;

  // Virtual memory interaction
  SpiRAM spiram;

  // inverted page table (physical mem number -> page number there)
  int invPageTable[16];
  // Page table (Page Number -> physical mem number)
  // -1 if not memory
  //int pageTable[1024];

  // Physical memory
  int physicalMem[TABLE_SIZE * PAGE_SIZE];
  int find(int pageNumber);
};
