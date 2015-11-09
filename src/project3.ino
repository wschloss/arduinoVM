#include "VM.h"
#define VECTOR_SIZE 5000
VM vm = VM();

int wordy(int virtAddress, int value = NULL){
    int val;
    Serial.println("================");
    Serial.print("requesting virtual address: ");
    Serial.println(virtAddress, DEC);
    Serial.print("page = ");
    Serial.print(virtAddress/PAGE_SIZE);
    Serial.print(", offset = ");
    Serial.println(virtAddress % PAGE_SIZE, DEC);
    int refs = vm.getFaultRate();
    if(value == NULL){
        val = vm[virtAddress];
    }
    else 
        vm[virtAddress] = value; if(vm.getFaultRate() > refs){
        Serial.println("PAGE FAULT!!"); Serial.println("NO SPACE IN PHYSICAL MEMORY"); Serial.print("Page OUT: ");
        Serial.println(vm.getLastPageOut(), DEC);
        Serial.print("Page IN: ");
        Serial.println(virtAddress/PAGE_SIZE);
        Serial.print("physical address: ");
        Serial.println(vm.getLastAddressIn());
    }
    delay(1000);
    return val;
}


void setup() {
    Serial.begin(57600);
    for(int i = 0; i < VECTOR_SIZE; i++){
        vm[i] = 1;
    }
    for(int i = VECTOR_SIZE; i < (VECTOR_SIZE*2)+1; i++){
        vm[i] = 1;
    }
}

void loop() {
   unsigned int sum = 0;
   unsigned int sum2 = 0;
   vm.resetFaultRate();
   for(int i = 0; i < VECTOR_SIZE; i++){
        if(VERBOSE){
            sum += wordy(i);
            sum2 += wordy(i+VECTOR_SIZE);
        }
        else{
            sum += vm[i];
            sum2 += vm[i+VECTOR_SIZE];
        }

   }
    Serial.print("Sum is: ");
    Serial.print(sum);
    Serial.println(", and Sum should = 5000");
    Serial.print("Sum 2 is: "); 
    Serial.print(sum2);
    Serial.println(", and Sum2 should = 5000");
    Serial.print("fault rate: ");
    Serial.println(vm.getFaultRate());
    vm.resetFaultRate();
    for(int i = 0 ; i < 1024 ; i++) {
       if(VERBOSE){
        wordy(i*32,5);
        
       }else {
        vm[i*32]=1;
       }
    }
    Serial.print("fault rate after thrashing: ");
    Serial.println(vm.getFaultRate());
    delay(2000);
}
