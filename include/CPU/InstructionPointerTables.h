//
// Created by plays on 6/18/2021.
//

#ifndef GBNEXT_INSTRUCTIONPOINTERTABLES_H
#define GBNEXT_INSTRUCTIONPOINTERTABLES_H
#include "CPU.h"
#include "Macroes/InstructionTemplateIndexes.h"
//The following syntax for a method pointer table was borrowed from the following file in destoer-emu
//https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
//It was not copy-pasted, but it very much uses the same format.

using OPCODE_HANDLER = void(CPU::*)(void);

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
            //TODO fill out opcode table

        };


#endif //GBNEXT_INSTRUCTIONPOINTERTABLES_H
