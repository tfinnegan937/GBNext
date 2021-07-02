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

using OPCODE_HANDLER = void (CPU::*)(int&); //A pointer to a method of the CPU class that takes an int& variable

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
            &CPU::ADD<REGHL,  REGHL>, //29
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
            &CPU::JR<JUMPCSET>, //38
            &CPU::ADD<REGHL, REGSP>, //39
            &CPU::LD<REGA, REGINDHLDEC>, //3A
            &CPU::DEC<REGSP>, //3B
            &CPU::INC<REGA>, //3C
            &CPU::DEC<REGA>, //3D
            &CPU::LD<REGA, IMMEDIATE8>, //3E
            &CPU::CCF, //3F
            &CPU::LD<REGB, REGB>, //40
            &CPU::LD<REGB, REGC>, //41
            &CPU::LD<REGB, REGD>, //42
            &CPU::LD<REGB, REGE>, //43
            &CPU::LD<REGB, REGH>, //44
            &CPU::LD<REGB, REGL>, //45
            &CPU::LD<REGB, REGINDHL>, //46
            &CPU::LD<REGB, REGA>, //47
            &CPU::LD<REGC, REGB>, //48
            &CPU::LD<REGC, REGC>, //49
            &CPU::LD<REGC, REGD>, //4A
            &CPU::LD<REGC, REGE>, //4B
            &CPU::LD<REGC, REGH>, //4C
            &CPU::LD<REGC, REGL>, //4D
            &CPU::LD<REGC, REGINDHL>, //4E
            &CPU::LD<REGC, REGA>, //4F
            &CPU::LD<REGD, REGB>, //50
            &CPU::LD<REGD, REGC>, //51
            &CPU::LD<REGD, REGD>, //52
            &CPU::LD<REGD, REGE>, //53
            &CPU::LD<REGD, REGH>, //54
            &CPU::LD<REGD, REGL>, //55
            &CPU::LD<REGD, REGINDHL>, //56
            &CPU::LD<REGD, REGA>, //57
            &CPU::LD<REGE, REGB>, //58
            &CPU::LD<REGE, REGC>, //59
            &CPU::LD<REGE, REGD>, //5A
            &CPU::LD<REGE, REGE>, //5B
            &CPU::LD<REGE, REGH>, //5C
            &CPU::LD<REGE, REGL>, //5D
            &CPU::LD<REGE, REGINDHL>, //5E
            &CPU::LD<REGE, REGA>, //5F
            &CPU::LD<REGH, REGB>, //60
            &CPU::LD<REGH, REGC>, //61
            &CPU::LD<REGH, REGD>, //62
            &CPU::LD<REGH, REGE>, //63
            &CPU::LD<REGH, REGH>, //64
            &CPU::LD<REGH, REGL>, //65
            &CPU::LD<REGH, REGINDHL>, //66
            &CPU::LD<REGH, REGA>, //67
            &CPU::LD<REGL, REGB>, //68
            &CPU::LD<REGL, REGC>, //69
            &CPU::LD<REGL, REGD>, //6A
            &CPU::LD<REGL, REGE>, //6B
            &CPU::LD<REGL, REGH>, //6C
            &CPU::LD<REGL, REGL>, //6D
            &CPU::LD<REGL, REGINDHL>, //6E
            &CPU::LD<REGL, REGA>, //6F
            &CPU::LD<REGINDHL, REGB>, //70
            &CPU::LD<REGINDHL, REGC>, //71
            &CPU::LD<REGINDHL, REGD>, //72
            &CPU::LD<REGINDHL, REGE>, //73
            &CPU::LD<REGINDHL, REGH>, //74
            &CPU::LD<REGINDHL, REGL>, //75
            &CPU::HALT, //76
            &CPU::LD<REGINDHL, REGA>, //77
            &CPU::LD<REGA, REGB>, //78
            &CPU::LD<REGA, REGC>, //79
            &CPU::LD<REGA, REGD>, //7A
            &CPU::LD<REGA, REGE>, //7B
            &CPU::LD<REGA, REGH>, //7C
            &CPU::LD<REGA, REGL>, //7D
            &CPU::LD<REGA, REGINDHL>, //7E
            &CPU::LD<REGA, REGA>, //7F
            &CPU::ADD<REGA, REGB>, //80
            &CPU::ADD<REGA, REGC>, //81
            &CPU::ADD<REGA, REGD>, //82
            &CPU::ADD<REGA, REGE>, //83
            &CPU::ADD<REGA, REGH>, //84
            &CPU::ADD<REGA, REGL>, //85
            &CPU::ADD<REGA, REGINDHL>, //86
            &CPU::ADD<REGA, REGA>, //87
            &CPU::ADC<REGA, REGB>, //88
            &CPU::ADC<REGA, REGC>, //89
            &CPU::ADC<REGA, REGD>, //8A
            &CPU::ADC<REGA, REGE>, //8B
            &CPU::ADC<REGA, REGH>, //8C
            &CPU::ADC<REGA, REGL>, //8D
            &CPU::ADC<REGA, REGINDHL>, //8E
            &CPU::ADC<REGA, REGA>, //8F

            //TODO fill out opcode table

        };


#endif //GBNEXT_INSTRUCTIONPOINTERTABLES_H
