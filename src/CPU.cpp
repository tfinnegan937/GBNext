//
// Created by plays on 6/16/2021.
//

#include "CPU/CPU.h"

CPU::CPU(shared_ptr<MemoryMap> memoryMap) {
    memory = memoryMap;

    A = 0x00;
    B = 0x00;
    C = 0x00;
    D = 0x00;
    E = 0x00;
    F = 0x00;
    H = 0x00;
    L = 0x00;
}

void CPU::Execute(int & cycles) {
    cycles--; //TODO PLACEHOLDER TO PREVENT HALT! Delete once instructions are implemented
}
