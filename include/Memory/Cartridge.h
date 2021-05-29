//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_CARTRIDGE_H
#define GBNEXT_CARTRIDGE_H
#include <memory>
#include "MemoryObject.h"
#include "MBC/MemoryBankController.h"
#include "MBC/MBC1.h"
#include "MBC/MBC2.h"
//Include the rest of the MBC files here.
class Cartridge : MemoryObject{
    std::unique_ptr<MemoryBankController> controller;

    bool ColorGB;

    MemoryBankController::BankEnum bankType;

    uint8_t ROMSize;
    uint8_t RAMSize;
public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    template<const uint16_t val>
    void LoadROM(std::array<uint8_t, val> array);
};


#endif //GBNEXT_CARTRIDGE_H
