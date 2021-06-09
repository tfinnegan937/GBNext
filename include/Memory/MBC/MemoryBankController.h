//
// Created by plays on 5/21/2021.
//

#ifndef GBNEXT_MEMORYBANKCONTROLLER_H
#define GBNEXT_MEMORYBANKCONTROLLER_H
#include "Memory/MemoryObject.h"
#include <vector>
#include <array>
#include <string>
#define BankType std::vector<std::array<uint8_t, 0x4000>>

class MemoryBankController : MemoryObject{
private:
public:
    enum BankEnum{
    ROMOnly,
    MBC1,
    MBC1Ram,
    MBC1RamBat,
    MBC2,
    MBC2Bat,
    MBC3,
    MBC3RAM,
    MBC3RAMBat,
    MBC5,
    MBC5RAM,
    MBC5RAMBat,
    };

    virtual void SwitchROMBank(uint16_t number) = 0;
    virtual void SwitchRAMBank(uint16_t number) = 0;

    void Initialize() override {};
    void WriteTo(uint8_t value, uint16_t location) override {};
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override{};
    uint8_t ReadAt(uint16_t location) override{return 0xFF;};
    virtual void LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) = 0;
    virtual void LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank)  = 0;
};


#endif //GBNEXT_MEMORYBANKCONTROLLER_H
