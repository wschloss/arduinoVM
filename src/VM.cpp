// CSCI442
// Project3

#include "VM.h"

int& VM::operator[](unsigned int address) {
  // Add to refs count
  refs++;
  // Translate address to a page and offset
  int pageNumber = address / PAGE_SIZE;
  int offset = address % PAGE_SIZE;

  // Check if the page is in memory
  int location = find(pageNumber);
  if (location == -1) {
    faults++;
    int data_stream[PAGE_SIZE];

    for (int i = nextPage*PAGE_SIZE; i < (nextPage+1)*PAGE_SIZE; ++i) {
        data_stream[i - nextPage*PAGE_SIZE] = physicalMem[i];
    }

    // Write based on spi page table
    spiram.write_ints(PAGE_SIZE * invPageTable[nextPage],data_stream, PAGE_SIZE);
    lastPageOut = invPageTable[nextPage];
    // Update page table and inv page table for the page that was swapped out
    //pageTable[invPageTable[nextPage]] = -1;
    invPageTable[nextPage] = pageNumber;
    
    // Read based on spi page table
    spiram.read_ints(pageNumber * PAGE_SIZE, data_stream, PAGE_SIZE);

    for (int i = nextPage*PAGE_SIZE; i < (nextPage+1)*PAGE_SIZE; ++i) {
        physicalMem[i] = data_stream[i - nextPage*PAGE_SIZE];
    }

    //pageTable[pageNumber] = nextPage*PAGE_SIZE;
    //if (pageNumber != nextPage)
    //    pageTable[nextPage] = -1;

    location = nextPage*PAGE_SIZE;
    nextPage = (nextPage + 1) % TABLE_SIZE;
    lastAddressIn = location;

  }

  // return the value
  return physicalMem[location + offset];
}

// Gets the fault rate
float VM::getFaultRate() {
    if(refs == 0)
        return 0;
  return (float)faults / refs;
}

// Resets the current fault rate
void VM::resetFaultRate() {
  faults = refs = 0;
}

int VM::find(int pageNumber) {
    int ret = -1;
    for (int i = 0; i < 16; ++i) {
        if (pageNumber == (invPageTable[i])) {
            ret = i * PAGE_SIZE;
            break;
        }
    }

    return ret;
}
