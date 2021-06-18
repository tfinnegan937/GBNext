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

uint8_t CPU::Fetch(int& cycles) {
    return memory->ReadAt(PC);
}

void CPU::Tick(int & cycles) {
    uint8_t ins = Fetch(cycles);
    DecodeAndExecute(ins, cycles); //Program Counter is Incremented in here
}

void CPU::DecodeAndExecute(uint8_t instruction, int & cycles) {
    PC+=4; //TODO REMOVE AFTER IMPLEMENTING INSTRUCTIONS
    cycles--; //TODO REMOVE AFTER IMPLEMENTING INSTRUCTIONS
}
