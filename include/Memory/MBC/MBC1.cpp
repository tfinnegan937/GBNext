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
            value = Bank0[curBank0Index][location];
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

        for(int i = 0; i < NumROMBanks - 1; i++){ //Subtract one ROM bank to account for bank 0
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

    //Bank zero can be switched between four banks in some carts.
    std::array<uint8_t, 0x4000> newBank{};
    newBank.fill(0x00);
    for(int i = 0; i < 4; i++){
        Bank0.push_back(newBank);
    }

    if(NumROMBanks < 32){
        maxBank0Index = 0;
    }else if(NumROMBanks < 64){
        maxBank0Index = 1;
    }else if(NumROMBanks < 96){
        maxBank0Index = 2;
    }else{
        maxBank0Index = 3;
    }

    RAMEnabled = false;

    curRAMBankIndex = 0;
    curROMBankIndex = 0;
    curBank0Index = 0;
}

void MBC1::SwitchROMBank(uint16_t number) {
    curROMBankIndex = number & 0x1F; //Input is only 5 bits

    //The below handles the fact that zero-first-nibble bank numbers always map to bank# + 1
    if(curROMBankIndex == 0x00 ){ //If the lower five bits are zero, increment them and check the upper two bits
                                  //And the banking mode in SwitchBank0
        curROMBankIndex++;
        SwitchBank0(number & 0xF0); //Does nothing if Banking mode is Simple.
    }

}

void MBC1::SwitchRAMBank(uint16_t number) {
    uint16_t masked = number & 0x03; // Input is only three bits
    if(NumRAMBanks > 1) {
        curRAMBankIndex = masked;
    }
}

MBC1::MBC1(int ROMBankCount, int RAMBankCount) {
    NumROMBanks = ROMBankCount;
    NumRAMBanks = RAMBankCount;
}

void MBC1::WriteRAMBank(uint8_t value, uint16_t location) {
        //The RAM bank number can be switched even if RAM is off.
        uint16_t index = location - RAMBankStart;
        RAMBanks[curRAMBankIndex][index] = value;
}

void MBC1::WriteROMBank(uint8_t value, uint16_t location) {
    //ROM, obviously, cannot be changed.
    //This function handles the functionality that occurs when specific
    //Areas of ROM are written to.

    if(location < 0x2000){ //RAM Enable Register

        if((value & 0x0F) == 0x0A && NumRAMBanks > 0){
            RAMEnabled = true;
        }else{
            RAMEnabled = false;
        }

    }else if(location < 0x4000){ //ROM Bank number
        if(NumROMBanks > 2){
            SwitchROMBank(value);
        }

    }else if(location < 0x6000 && mode == Advanced){ //High ROM Bank Number/ RAM Bank Number

        if(NumROMBanks > 32) {
            //Bank index is 5 bits, this region is the upper two bits.
            //In case the index is higher than the masked value for whatever
            //reason, we zero-mask the two most significant bits.
            SwitchROMBank(((value & 0x03) << 5) + (curROMBankIndex & 0x1F));
        }
        if(NumRAMBanks > 1){
            SwitchRAMBank(value);
        }

    }else if(location < 0x8000){ //Banking Mode
        uint8_t advanced = value & 0x01;

        if(advanced){
            mode = Advanced;
        }else{
            mode = Simple;
        }
    }else{
        throw(std::runtime_error("Attempt to write to ROM value greater than 0x7FFF"));
    }

}

uint8_t MBC1::ReadROMBank(uint16_t location) {
    uint16_t index = location - ROMBankStart;
    return ROMBanks[curROMBankIndex][index];
}

uint8_t MBC1::ReadRAMBank(uint16_t location) {
    if(RAMEnabled) {
        uint16_t index = location - RAMBankStart;
        if(mode == Advanced && NumRAMBanks > 1) { //Advanced banking mode
            return RAMBanks[curRAMBankIndex][index];
        }else{
            return RAMBanks[0][index]; //Simple Banking Mode
        }
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

void MBC1::SwitchBank0(uint16_t number) {
    if(mode == Advanced && NumROMBanks > 32){
        switch(number){
            case 0x20:
                curBank0Index = 1;
                break;
            case 0x40:
                curBank0Index = 2;
            case 0x60:
                curBank0Index = 3;
                break;
            default: //Set to 0x00 or any other value
                curBank0Index = 0;
                break;
        }
    }
}




