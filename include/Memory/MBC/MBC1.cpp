//
// Created by plays on 5/21/2021.
//

#include "MBC1.h"
#define RAMBankStart 0xA000
#define ROMBankStart 0x4000

void MBC1::WriteTo(uint8_t value, uint16_t location) {
    Region region = GetRegion(location);
    switch(region){
        case RegRAMBank:
            WriteRAMBank(value, location);
            break;
        default:
            WriteROMBank(value, location);
            break;
    }

}

uint8_t MBC1::ReadAt(uint16_t location) {
    Region region = GetRegion(location);
    uint8_t value = 0x00;
    switch(region){
        case RegBank0:
            value = Bank0[location];
            break;
        case RegROMBank:
            value = ReadROMBank(location);
            break;
        case RegRAMBank:
            value = ReadRAMBank(location);
            break;
    }
    return value;
}

void MBC1::WriteRange(uint8_t value, uint16_t start, uint16_t end) {

    for(int i = start; i < end; i++){
        WriteTo(value, i);
    }
}

void MBC1::Initialize() {

    if(NumROMBanks > 0){
        NumROMBanks = NumROMBanks + 4; //Not particularly memory-efficient
                                       //But it accounts for the fact that banks $00, $20, $40, and $60
                                       //map to (bank# + 1). Also handled in SwitchROMBank.
        for(int i = 0; i < NumROMBanks; i++){
            std::array<uint8_t, 0x4000> newBank{};
            newBank.fill(0x00);
            ROMBanks.push_back(newBank);
        }
    }

    if(NumRAMBanks > 0){
        for(int i = 0; i < NumRAMBanks; i++){
            std::array<uint8_t, 0x4000> newBank{};
            newBank.fill(0x00);
            RAMBanks.push_back(newBank);
        }
    }

    Bank0.fill(0x00);
    RAMEnabled = false;

    curRAMBankIndex = 0;
    curROMBankIndex = 0;
}

void MBC1::SwitchROMBank(uint16_t number) {
    curROMBankIndex = number;

    //The below handles the fact that zero-first-nibble bank numbers always map to bank# + 1
    if((number & 0x0F) == 0x00){
        curROMBankIndex++;
    }

}

void MBC1::SwitchRAMBank(uint16_t number) {
    curRAMBankIndex = number;
}

MBC1::MBC1(int ROMBankCount, int RAMBankCount) {
    NumROMBanks = ROMBankCount;
    NumRAMBanks = RAMBankCount;
}

void MBC1::WriteRAMBank(uint8_t value, uint16_t location) {
    if(RAMEnabled) {
        uint16_t index = location - RAMBankStart;
        RAMBanks[curRAMBankIndex][index] = value;
    }
}

void MBC1::WriteROMBank(uint8_t value, uint16_t location) {
    //ROM, obviously, cannot be changed.
    //This function handles the functionality that occurs when specific
    //Areas of ROM are written to.
    if(location < 0x2000){
        uint8_t check = value & 0x0F;
        switch(check){
            case 0x00:
                RAMEnabled = true;
                break;
            case 0x0A:
                RAMEnabled = false;
                break;
            default:
                //Do nothing
                break;
        }
    }else if(location < 0x4000){ //TODO Handle larger ROM Bank Spaces
        SwitchROMBank(value);
    }else if(location < 0x5FFF){
        SwitchRAMBank(value);
    }else if(location < 0x7FFF){
        //TODO Handle banking mode.
    }else{
        //TODO Handle Error
    }

}

uint8_t MBC1::ReadROMBank(uint16_t location) {
    uint16_t index = location - ROMBankStart;
    return ROMBanks[curROMBankIndex][index];
}

uint8_t MBC1::ReadRAMBank(uint16_t location) {
    if(RAMEnabled) {
        uint16_t index = location - RAMBankStart;
        return RAMBanks[curRAMBankIndex][index];
    }else{
        return 0xFF; //THIS WILL NOT WORK WITH SOME BUGGED GAMES
    }
}

MBC1::Region MBC1::GetRegion(uint16_t location) {
    if(location < 0x4000){
        return RegBank0;
    }else if (location < 0x8000){
        return RegROMBank;
    }else if (location < 0xA000){
        throw(std::runtime_error("Error: Video Memory Access from ROM Memory"));
    }else if (location < 0xC000){
        return RegRAMBank;
    }else{
        throw(std::runtime_error("Error: Memory location requested from ROM is greater than cartridge region"));
    }
}




