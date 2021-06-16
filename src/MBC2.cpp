//
// Created by plays on 5/28/2021.
//

#include "Memory/MBC/MBC2.h"

void MBC2::WriteTo(uint8_t value, uint16_t location, bool ppuMode2) {
    if(location < 0x4000){
        HandleRegisterWrite(value, location);
    }else if (location < 0x8000){
        //Do Nothing
    }else if (location < 0xA000){
        throw(std::runtime_error("Error: Video Memory address written to MBC2"));
    }else if(location < 0xA200){
        RAM[location - 0xA000] = value & 0x0F;
    }else if(location < 0xC000){
        RAM[location - 0xA200]  = value & 0x0f;
    }else{
        throw(std::runtime_error("Error: Address passed to MBC2 > 0xBFFF"));
    }
}

uint8_t MBC2::ReadAt(uint16_t location, bool ppuMode2) {
    Region region = GetRegion(location);
    switch(region){
        case Bank0:
            return ROMBanks[0][location];
            break;
        case Banks:
            return ROMBanks[curBankIndex][location];
            break;
        case Mem:
            if(RAMEnabled){
                return RAM[location - 0xA000] & 0x0F;
            }
            return 0xFF;
            break;
        case MemEcho:
            if(RAMEnabled){
                return RAM[location - 0xA200];
            }
            return 0xFF;
            break;
    }
    return 0x00;
}

void MBC2::WriteRange(uint8_t value, uint16_t start, uint16_t end) {

    for(int i = start; i < end; i++){
        WriteTo(value, i, false);
    }
}

void MBC2::Initialize() {

    for(int i = 0; i < ROMBankCount; i++){
        std::array<uint8_t, 0x4000> newBank{};
        newBank.fill(0x00);

        ROMBanks.push_back(newBank);
    }
    RAM.fill(0x00);
}

void MBC2::SwitchBank0(uint16_t number) {
    throw(std::runtime_error("Bank0 switch attempted on MBC2. Not supported"));
}

void MBC2::SwitchROMBank(uint16_t number) {
    curBankIndex = number;

    if(curBankIndex > ROMBankCount - 1){
        curBankIndex -= (ROMBankCount - 1);
    }
    if(curBankIndex == 0) {
        curBankIndex++;
    }
}

void MBC2::SwitchRAMBank(uint16_t number) {
throw(std::runtime_error("RAM Bank Switch attempted on MBC2. Not supported"));
}

MBC2::MBC2(int NumROMBanks) {
    if(NumROMBanks > 16){
        throw(std::runtime_error("Error: MBC2 can have no more than 16 banks"));
    }
    if(NumROMBanks <= 0){
        throw(std::runtime_error("Error: MBC2 must have at least one ROM bank"));
    }
    ROMBankCount = NumROMBanks;
}

MBC2::Region MBC2::GetRegion(uint16_t address) {
    if(address < 0x4000){
        return Bank0;
    }else if(address < 0x8000){
        return Banks;
    }else if(address < 0xA1FF){
        return Mem;
    }else if (address < 0xC000){
        return MemEcho;
    }else{
        throw(std::runtime_error("Invalid address passed to MBC2"));
    }
}

void MBC2::HandleRegisterWrite(uint8_t value, uint16_t location) {
    uint16_t Bit8 = (location & 0xF0) >> 8;

    if(Bit8){
        SwitchROMBank(value);
    }else{
        switch(value){
            case 0x0A:
                RAMEnabled = true;
                break;
            default:
                RAMEnabled = false;
                break;
        }
    }
}

void MBC2::LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    ROMBanks[index] = bank;
}

void MBC2::LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    auto temp = bank;
    for(int i = 0; i < 512; i++){ //On-Board RAM contains 512 nibbles
        temp[i] = bank[i] & 0x0F; //Remove leading four bits
    }

    if(index > 0){
        throw(std::runtime_error("Error: MBC2 only has a single RAM bank of 512 nibbles"));
    }

    for(int i = 0; i < 512; i++){
        RAM[i] = temp[i];
    }
}
