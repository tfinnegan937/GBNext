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
#include "MBC/NoMBC.h"
//Include the rest of the MBC files here.
class Cartridge : MemoryObject{
    std::unique_ptr<MemoryBankController> controller;

    bool ColorGB;

    MemoryBankController::BankEnum bankType;

    uint8_t ROMSize;
    uint8_t RAMSize;

    void SelectBankType(uint8_t descriptor); //Gets the bank type from the cartridge header value
    void SelectROMSize(uint8_t descriptor); //Gets the ROM size from the cartridge header value
    void SelectRAMSize(uint8_t descriptor); //Gets the RAM Size from the cartridge header value
    void CreateControllerObject(); //Takes the ROM Size, RAM Size, and bank type and generates the MBC object
public:
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;

    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    void LoadROM(uint8_t * arr, int val);
};


#endif //GBNEXT_CARTRIDGE_H
