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
    throw(std::runtime_error("Error: ROM banks not present on cart without a Bank Controller"));
}

void NoMBC::SwitchRAMBank(uint16_t number) {
    throw(std::runtime_error("Error: RAM banks not present on cart without a bank controller"));
}

void NoMBC::LoadROM(std::array<uint8_t, 0x8000> byteArray) {
    for(int i = 0; i < 0x8000; i++){
        ROM[i] = byteArray[i];
    }
}
