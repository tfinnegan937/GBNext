//
// Created by plays on 5/21/2021.
//

#ifndef GBNEXT_MEMORYBANKCONTROLLER_H
#define GBNEXT_MEMORYBANKCONTROLLER_H
#include "Memory/MemoryObject.h"

class MemoryBankController : MemoryObject{
private:
public:
    enum BankType{
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
};


#endif //GBNEXT_MEMORYBANKCONTROLLER_H
