//
// Created by plays on 5/21/2021.
//

#ifndef GBNEXT_MEMORYBANKCONTROLLER_H
#define GBNEXT_MEMORYBANKCONTROLLER_H
#include "Memory/MemoryObject.h"

class MemoryBankController {
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

    virtual void SwitchROMBank(int number) = 0;
    virtual void SwitchRAMBank(int number) = 0;
};


#endif //GBNEXT_MEMORYBANKCONTROLLER_H
