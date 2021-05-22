//
// Created by plays on 5/21/2021.
//

#ifndef GBNEXT_MBC1_H
#define GBNEXT_MBC1_H


#include <Memory/MemoryObject.h>
#include "MemoryBankController.h"
#include <vector>
#include <array>

#define BankType std::vector<std::array<uint8_t, 0x4000>>

class MBC1 : MemoryBankController{
private:
    enum Region{
        RegBank0,
        RegRAMBank,
        RegROMBank
    };
    uint8_t NumROMBanks;
    uint8_t NumRAMBanks;
    bool RAMEnabled;
    std::array<uint8_t, 0x4000> Bank0;
    BankType ROMBanks;
    BankType RAMBanks;

    uint16_t curROMBankIndex;

    uint16_t curRAMBankIndex;

    void WriteROMBank(uint8_t value, uint16_t location);
    void WriteRAMBank(uint8_t value, uint16_t location);
    uint8_t ReadROMBank(uint16_t location);
    uint8_t ReadRAMBank(uint16_t location);
    Region GetRegion(uint16_t location);
public:
    void WriteTo(uint8_t value, uint16_t location) override;
    uint8_t ReadAt(uint16_t location) override;
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;
    void Initialize() override;
    void SwitchROMBank(uint16_t number) override;
    void SwitchRAMBank(uint16_t number) override;
    MBC1(int ROMBankCount, int RAMBankCount);

};


#endif //GBNEXT_MBC1_H