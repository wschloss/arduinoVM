// CSCI442
// Project3

#include "VM.h"

int& VM::operator[](int address) {
  // Add to refs count
  refs++;
  // Translate address to a page and offset
  int pageNumber = address / PAGE_SIZE;
  int offset = address % PAGE_SIZE;

  // Check if the page is in memory
  int location = pageTable[pageNumber];
  if (location == -1) {
    // SWAP PAGE IN
    //
    // swap next page out
    // swap page in
    // update page table
    // update location variable
  }

  // return the value
  return physicalMem[location + offset];
}

// Gets the fault rate
float VM::getFaultRate() {
  return faults / refs;
}

// Resets the current fault rate
void VM::resetFaultRate() {
  faults = refs = 0;
}
