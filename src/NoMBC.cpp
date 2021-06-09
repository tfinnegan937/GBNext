//
// Created by plays on 5/29/2021.
//

#include "Memory/MBC/NoMBC.h"

void NoMBC::WriteTo(uint8_t value, uint16_t location) {
    if(location > 0x7FFF){
        throw(std::runtime_error("Error: Non-ROM region written to through ROM"));
    }
}

uint8_t NoMBC::ReadAt(uint16_t location) {
    if(location < 0x7FFF){
        return ROM[location];
    }else if(location < 0x9FFF){
        throw(std::runtime_error("Error: Attempt to read from VRAM from ROM"));
    }else if(location < 0xBFFF){
        return 0xFF; //No RAM available.
    }else{
        throw(std::runtime_error("Error: Non-ROM region read from through ROM"));
    }
}

void NoMBC::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    MemoryBankController::WriteRange(value, start, end);
}

void NoMBC::Initialize() {
    ROM.fill(0x00);
}

void NoMBC::SwitchBank0(uint16_t number) {
    throw(std::runtime_error("Error: Bank0 cannot be swapped on a cart without a Bank Controller"));
}

void NoMBC::SwitchROMBank(uint16_t number) {
    throw(std::runtime_error("Error: ROM banks not present on a cart without a Bank Controller"));
}

void NoMBC::SwitchRAMBank(uint16_t number) {
    throw(std::runtime_error("Error: RAM banks not present on a cart without a bank controller"));
}

void NoMBC::LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    uint16_t offset = 0x0000;
    switch(index){
        case 0:
            offset = 0x0000;
            break;
        case 1:
            offset = 0x4000;
            break;
        default:
            throw(std::runtime_error("This cartridge does not have ROM banks. This emulator abstracts\n"
                                     "the contiguous ROM as Bank 0 at offset 0, and Bank 1 at offset 0x4000\n"
                                     "while loading ROM file.\n"));
    }

    for(int i = offset; i < 0x4000 + offset; i++){
        ROM[i] = bank[i];
    }
}

void NoMBC::LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    throw(std::runtime_error("RAM Banks not implemented on any official non-MBC cartridge"));
}


