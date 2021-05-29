//
// Created by plays on 5/29/2021.
//

#ifndef GBNEXT_NOMBC_H
#define GBNEXT_NOMBC_H

#include "MemoryBankController.h"

class NoMBC : MemoryBankController{
    std::array<uint8_t, 0x8000> ROM;
private:
    void WriteTo(uint8_t value, uint16_t location) override;
    uint8_t ReadAt(uint16_t location) override;
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;
    void Initialize() override;
    void SwitchBank0(uint16_t number);
    void SwitchROMBank(uint16_t number) override;
    void SwitchRAMBank(uint16_t number) override;

    void LoadROM(std::array<uint8_t, 0x8000> byteArray);
};


#endif //GBNEXT_NOMBC_H
