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

class CPU final {
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
    //Von Neumann Functions
    uint8_t Fetch(int & cycles);
    void DecodeAndExecute(uint8_t instruction, int & cycles);
    void Tick(int & cycles);

    //CPU INSTRUCTIONS
    //They are ordered by when they first appear in this table: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
    void NOP(int & cycles);

    template<const int firstType, const int secondType>
    void LD(int & cycles);

    template<const int type>
    void INC(int & cycles);

    template<const int type>
    void DEC(int & cycles);

    void RLCA(int & cycles);

    template<const int firstType, const int secondType>
    void ADD(int & cycles);

    void RRCA(int & cycles);

    void STOP(int & cycles); //TWO BYTES LONG. There is a zero after the opcode

    void RLA(int & cycles);

    template<const int condition>
    void JR(int & cycles);

    void RRA(int & cycles);

    void DAA(int & cycles);

    void CPL(int & cycles);

    void SFC(int & cycles);

    void CCF(int & cycles);

    void HALT(int & cycles);

    template<const int firstType, const int secondType>
    void ADC(int & cycles);

    template<const int type>
    void SUB(int & cycles);

    template<const int firstType, const int secondType>
    void SBC(int & cycles);

    template<const int type>
    void AND(int & cycles);

    template <const int type>
    void XOR(int & cycles);

    template<const int type>
    void OR(int & cycles);

    template<const int type>
    void CP(int & cycles);

    template<const int type>
    void RET(int & cycles);

    template<const int type>
    void POP(int & cycles);

    template<const int type>
    void JP(int & cycles);

    template<const int type>
    void CALL(int & cycles);

    template<const int type>
    void PUSH(int & cycles);

    template<const int type>
    void RST(int & cycles);

    void PREFIXCB(int & cycles);

    void RETI(int & cycles);

    template<const int firstType, const int secondType>
    void LDH(int & cycles);

    void DI(int & cycles);

    void EI(int & cycles);

    //CB PREFIXED INSTRUCTIONS


};


#endif //GBNEXT_CPU_H
