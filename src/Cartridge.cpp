//
// Created by tfinnegan on 5/7/21.
//

#include "../include/Memory/Cartridge.h"
#include <string>
uint8_t Cartridge::ReadAt(uint16_t location) {
    return 0;
}

void Cartridge::WriteTo(uint8_t value, uint16_t location) {

}

void Cartridge::WriteRange(uint8_t value, uint16_t start, uint16_t end) {

}

void Cartridge::Initialize() {
    ColorGB = false;
}

template<const uint16_t val>
void Cartridge::LoadROM(std::array<uint8_t, val> array) {
    //Mapped according to the table at https://gbdev.io/pandocs/The_Cartridge_Header.html
    uint8_t cartType = 0x00;
    if(val < 0x147){
        throw (std::runtime_error("Byte Array too small to be complete cart."));
    }
    cartType = array[0x147];

    switch(cartType){
        case 0x00:
            bankType = MemoryBankController::ROMOnly;
            break;
        case 0x01:
            bankType = MemoryBankController::MBC1;
            break;
        case 0x02:
            bankType = MemoryBankController::MBC1Ram;
            break;
        case 0x03:
            bankType = MemoryBankController::MBC1RamBat;
            break;
        case 0x05:
            bankType = MemoryBankController::MBC2;
            break;
        case 0x06:
            bankType = MemoryBankController::MBC2Bat;
            break;
        default:
            throw(std::runtime_error("This cartridge type is currently unsupported"));
    }



}
