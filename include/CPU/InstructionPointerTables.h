//
// Created by plays on 6/18/2021.
//

#ifndef GBNEXT_INSTRUCTIONPOINTERTABLES_H
#define GBNEXT_INSTRUCTIONPOINTERTABLES_H
#include "CPU.h"
#include "Macroes/InstructionTemplateIndexes.h"
//The following syntax for a method pointer table was borrowed from the following file in destoer-emu
//https://github.com/destoer/destoer-emu/blob/master/src/headers/gb/opcode_table.h
//It was not copy-pasted, but it very much uses the same format.

using OPCODE_HANDLER = void (CPU::*)(int&); //A pointer to a method of CPU that takes an int& variable

const OPCODE_HANDLER opcode_table[256] =
        {
            &CPU::NOP, //00
            &CPU::LD<REGBC, IMMEDIATE16>, //01
            &CPU::LD<REGINDBC, REGA>,  //02
            &CPU::INC<REGBC>, //03
            &CPU::INC<REGB>, //04
            &CPU::DEC<REGB>, //05
            &CPU::LD<REGB, IMMEDIATE8>,//06
            &CPU::RLCA, //07
            &CPU::LD<INDIRECTADDRESS16, REGSP>, //08
            &CPU::ADD<REGHL, REGBC>, //09
            &CPU::LD<REGA, REGINDBC>, //0A
            &CPU::DEC<REGBC>, //0B
            &CPU::INC<REGC>,  //0C
            &CPU::DEC<REGC>, //0D
            &CPU::LD<REGC, IMMEDIATE8>, //0E
            &CPU::RRCA, //0F
            &CPU::STOP, //10
            &CPU::LD<REGDE, IMMEDIATE16>, //11
            &CPU::LD<REGINDDE, REGA>, //12
            &CPU::INC<REGDE>,//13
            &CPU::INC<REGD>, //14
            &CPU::DEC<REGD>, //15
            &CPU::LD<REGD, IMMEDIATE8>,//16
            &CPU::RLA, //17
            &CPU::JR<JUMPNOCONDITION>, //18
            &CPU::ADD<REGHL, REGDE>, //19
            &CPU::LD<REGA, REGINDDE>, //1A
            &CPU::DEC<REGDE>, //1B
            &CPU::INC<REGE>, //1C
            &CPU::DEC<REGE>, //1D
            &CPU::LD<REGE, IMMEDIATE8>, //1E
            &CPU::RRA, //1F
            &CPU::JR<JUMPZRESET>, //20
            &CPU::LD<REGHL, IMMEDIATE16>,//21
            &CPU::LD<REGINDHLINC, REGA>, //22
            &CPU::INC<REGHL>, //23
            &CPU::INC<REGH>, //24
            &CPU::DEC<REGH>, //25
            &CPU::LD<REGH, IMMEDIATE8>, //26
            &CPU::DAA, //27
            &CPU::JR<JUMPZSET>, //28
            &CPU::ADD<REGHL, REGHL>, //29
            &CPU::LD<REGA, REGINDHLINC>, //2A
            &CPU::DEC<REGHL>, //2B
            &CPU::INC<REGL>, //2C
            &CPU::DEC<REGL>, //2D
            &CPU::LD<REGL, IMMEDIATE8>, //2E
            &CPU::CPL, //2F
            &CPU::JR<JUMPCRESET>, //30
            &CPU::LD<REGSP, IMMEDIATE16>, //31
            &CPU::LD<REGINDHLDEC, REGA>, //32
            &CPU::INC<REGSP>, //33
            &CPU::INC<REGINDHL>, //34
            &CPU::DEC<REGINDHL>, //35
            &CPU::LD<REGINDHL, IMMEDIATE8>, //36
            &CPU::SCF, //37





            //TODO fill out opcode table

        };


#endif //GBNEXT_INSTRUCTIONPOINTERTABLES_H
