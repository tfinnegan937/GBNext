//
// Created by plays on 5/28/2021.
//

#ifndef GBNEXT_MBC2_H
#define GBNEXT_MBC2_H
#include "MemoryBankController.h"

class MBC2 : MemoryBankController{
private:
    enum Region{
        Bank0, //First ROM region
        Banks, //Second ROM region
        Mem, //RAM
        MemEcho, //Echo of the RAM
    };
    BankType ROMBanks;
    std::array<uint8_t, 512> RAM{};
    uint8_t curBankIndex = 1;
    int ROMBankCount;
    bool RAMEnabled = false;

    void HandleRegisterWrite(uint8_t value, uint16_t location);
    Region GetRegion(uint16_t address);
public:
    void WriteTo(uint8_t value, uint16_t location) override;
    uint8_t ReadAt(uint16_t location) override;
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;
    void Initialize() override;
    void SwitchBank0(uint16_t number);
    void SwitchROMBank(uint16_t number) override;
    void SwitchRAMBank(uint16_t number) override;
    MBC2(int NumROMBanks);

    void LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;
    void LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;
};


#endif //GBNEXT_MBC2_H
