//
// Created by plays on 6/16/2021.
//

#ifndef GBNEXT_CPU_H
#define GBNEXT_CPU_H


#include <cstdint>
#include <memory>
#include "CPU/RegisterUnion.h"
#include "Memory/MemoryMap.h"

using namespace std;

class CPU {
private:
    uint16_t SP = 0x0000;
    uint16_t PC = 0x0000;

    uint8_t A;
    uint8_t F;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;

    //These variables provide 16 bit operations using internal pointers to the 8-bit registers
    //They simply overload the binary and a few unary operators.
    //Assignment, Arithmetic, increment/decrement, and Boolean operators are supported
    //Assigning a RegisterUnion to a RegisterUnion will copy the pointers, not the values
    //Assigning a value from RegisterUnion BC to RegisterUnion AF would look like such:
    //AF = BC.get()
    RegisterUnion AF = RegisterUnion(&A, &F);
    RegisterUnion BC = RegisterUnion(&B, &C);
    RegisterUnion DE = RegisterUnion(&D, &E);
    RegisterUnion HL = RegisterUnion(&H, &L);

    shared_ptr<MemoryMap> memory;
public:
    explicit CPU(shared_ptr<MemoryMap> memoryMap);
    void Execute(int & cycles);
};


#endif //GBNEXT_CPU_H
