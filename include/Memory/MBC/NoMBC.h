//
// Created by plays on 5/29/2021.
//

#ifndef GBNEXT_NOMBC_H
#define GBNEXT_NOMBC_H

#include "MemoryBankController.h"

class NoMBC : public MemoryBankController{
    std::array<uint8_t, 0x8000> ROM;
private:
    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;
    void Initialize() override;
    void SwitchBank0(uint16_t number);
    void SwitchROMBank(uint16_t number) override;
    void SwitchRAMBank(uint16_t number) override;

   void LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;
   void LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;

public:
   NoMBC(int NumROMBanks, int NumRAMBanks);
};


#endif //GBNEXT_NOMBC_H
