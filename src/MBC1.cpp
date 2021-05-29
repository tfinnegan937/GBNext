//
// Created by plays on 5/21/2021.
//

#include "Memory/MBC/MBC1.h"
#define RAMBankStart 0xA000
#define ROMBankStart 0x4000
#include <iostream>
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

    if(NumROMBanks < 32){
        maxBank0Index = 0;
    }else if(NumROMBanks < 64){
        maxBank0Index = 1;
    }else if(NumROMBanks < 96){
        maxBank0Index = 2;
    }else{
        maxBank0Index = 3;
    }

    if(NumROMBanks > 0){
        uint16_t ROMBankIndex = NumROMBanks + maxBank0Index; //Not particularly memory-efficient
                                       //But it accounts for the fact that banks $00, $20, $40, and $60
                                       //map to (bank# + 1). Also handled in SwitchROMBank.

        for(int i = 0; i < ROMBankIndex-1; i++){ //Subtract one Cartridge bank to account for bank 0
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
    for(int i = 0; i < maxBank0Index + 1; i++){
        Bank0.push_back(newBank);
    }



    RAMEnabled = false;

    curRAMBankIndex = 0;
    curROMBankIndex = 0;
    curBank0Index = 0;

    ROMBankRegister = 0x00;
    RAMBankRegister = 0x00;
}

void MBC1::SwitchROMBank(uint16_t number) {
    //Roll over if max number of Cartridge banks is exceeded.
    uint16_t adjusted_num = number;
    while(adjusted_num > NumROMBanks){
        adjusted_num -= NumROMBanks;
    } //TODO Stop using the indices as registers. Create register variables and read/write to those
      //Before switching banks
    curROMBankIndex = adjusted_num; //Input is only 5 bits
    //The below handles the fact that zero-first-nibble bank numbers always map to bank# + 1
    if((adjusted_num & 0x1F) == 0x00 ){ //If the lower five bits are zero, increment them and check the upper two bits
                                  //And the banking mode in SwitchBank0
        curROMBankIndex++;
        SwitchBank0(adjusted_num & 0x60); //Does nothing if Banking mode is Simple.
    }

}

void MBC1::SwitchRAMBank(uint16_t number) {
    uint16_t masked = number & 0x03; // Input is only three bits

    //Mask to maximum number of RAM banks.
    //Roll over if exceeded.
    while(masked > NumRAMBanks){
        masked -= NumRAMBanks;
    }
    //RAM bank only changes if RAM banking is present
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
        if(RAMEnabled) {
            uint16_t index = location - RAMBankStart;
            uint16_t debug_index = curRAMBankIndex;
            RAMBanks[debug_index][index] = value;
        }
}

void MBC1::WriteROMBank(uint8_t value, uint16_t location) {
    //Cartridge, obviously, cannot be changed.
    //This function handles the functionality that occurs when specific
    //Areas of Cartridge are written to.

    if(location < 0x2000){ //RAM Enable Register

        if((value & 0x0F) == 0x0A && NumRAMBanks > 0){
            RAMEnabled = true;
        }else{
            RAMEnabled = false;
        }

    }else if(location < 0x4000){ //Cartridge Bank number
        if(NumROMBanks > 2){
            ROMBankRegister = value & 0x1F;
            //Change JUST the ROM Bank Register and then swap the whole value
            SwitchROMBank((RAMBankRegister << 5) ^ ROMBankRegister);
        }

    }else if(location < 0x6000 && mode == Advanced){ //High Cartridge Bank Number/ RAM Bank Number

        if(NumROMBanks > 32) {
            RAMBankRegister = value & 0x03;
            //Change JUST the RAM Bank register and then swap the whole value.
            SwitchROMBank((RAMBankRegister << 5) ^ ROMBankRegister);
        }
        else if(NumRAMBanks > 1){
            RAMBankRegister = value & 0x03;
            SwitchRAMBank(value);
        }

    }else if(location < 0x8000){ //Banking Mode
        uint8_t advanced = value & 0x01; //All bits aside from bit 0 are don't cares.

        if(advanced){
            mode = Advanced;
        }else{
            mode = Simple;
        }
    }else{
        throw(std::runtime_error("Attempt to write to Cartridge value greater than 0x7FFF"));
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
        throw(std::runtime_error("Error: Video Memory Access from Cartridge Memory -- " + std::to_string(location)));
    }else if (location < 0xC000){
        return RegRAMBank;
    }else{
        throw(std::runtime_error("Error: Memory location requested from Cartridge is greater than cartridge region " + std::to_string(location)));
    }
}

void MBC1::SwitchBank0(uint16_t number) {
    if(mode == Advanced && NumROMBanks > 31){
        switch(number){
            case 0x20:
                curBank0Index = 1;
                break;
            case 0x40:
                curBank0Index = 2;
                break;
            case 0x60:
                curBank0Index = 3;
                break;
            default: //Set to 0x00 or any other value
                curBank0Index = 0;
                break;
        }
    }
}

void MBC1::LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    if(index % 0x20 == 0 && index <= 0x60){
        //This branch accounts for Bank Numbers 0x00, 0x20, 0x40, and 0x60
        //stored at 0x0000-0x3FFF
        Bank0[index] = bank;
    }else{
        ROMBanks[index] = bank;
    }
}

void MBC1::LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) {
    uint16_t mask = index & 0x03;

    RAMBanks[mask] = bank;
}

std::string MBC1::GetDebugInformation() {
    std::string output = "\n";

    output += "Expected Number of RAM Banks: " + std::to_string(NumRAMBanks) + "\n";
    output += "Actual Number of RAM Banks: " + std::to_string(RAMBanks.size()) + "\n";
    output += "Current RAM Bank Index: " + std::to_string(curRAMBankIndex) + "\n";
    output += "Expected Number of ROM Banks: " + std::to_string(NumROMBanks) + "\n";
    //3 is subtracted from this number to account for the four empty ROM banks added in Initialize()
    //To keep the indexing consistent
    output += "Actual Number of ROM Banks: " + std::to_string(ROMBanks.size() + Bank0.size()) + "\n";
    output += "Of which " + std::to_string(Bank0.size()) + " Are stored in Bank0,\n";
    output += std::to_string(ROMBanks.size()) + " Are stored in the Simple ROM Bank region, \n";
    output += "And of which " + std::to_string(maxBank0Index + 1) + " Are filler banks (Placeholder banks in Simple Bank region)\n";
    output += "Current Bank0 Index: " + std::to_string(curBank0Index) + "\n";
    output += "Current ROM Bank Index: " + std::to_string(curROMBankIndex) + "\n";
    output += "Banking Mode: " + std::to_string((int)mode) + "\n";
    output += "RAM Enabled: ";

    if(RAMEnabled){
        output+= "true\n";
    }else{
        output += "false\n";
    }
    return output;
}



