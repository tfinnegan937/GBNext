//
// Created by plays on 5/21/2021.
//

#include "MBC1.h"

void MBC1::WriteTo(uint8_t value, uint16_t location) {

}

uint8_t MBC1::ReadAt(uint16_t location) {
    return 0;
}

void MBC1::WriteRange(uint8_t value, uint16_t start, uint16_t end) {

}

void MBC1::Initialize() {

    if(NumROMBanks > 0){
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

    RAMEnabled = false;

    curRAMBankIndex = 0;
    curROMBankIndex = 0;
}

void MBC1::SwitchROMBank(int number) {
    curROMBankIndex = number;
}

void MBC1::SwitchRAMBank(int number) {
    curRAMBankIndex = number;
}

MBC1::MBC1(int ROMBankCount, int RAMBankCount) {
    NumROMBanks = ROMBankCount;
    NumRAMBanks = RAMBankCount;
}

void MBC1::SetRAMEnabled(bool enabled) {
    RAMEnabled = enabled;
}
