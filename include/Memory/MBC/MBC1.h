//
// Created by plays on 5/21/2021.
//

#ifndef GBNEXT_MBC1_H
#define GBNEXT_MBC1_H


#include <Memory/MemoryObject.h>
#include "MemoryBankController.h"
#include <vector>
#include <array>
#include <string>

class MBC1 : public MemoryBankController{
private:
    //Given a memory region, what part of the cartridge is it stored in?
    enum Region{
        RegBank0,
        RegRAMBank,
        RegROMBank
    };
    //Simple Banking with No RAM, or Banking + (RAM or Advanced Banking)
    enum BankingMode{
        Simple,
        Advanced
    };

    BankingMode mode = Simple;

    //Determined by cartridge header. Passed to MBC1 by Cartridge object that creates it
    uint8_t NumROMBanks;
    uint8_t NumRAMBanks;

    //Must be true to read anything other than 0xFF from RAM
    bool RAMEnabled;

    //See Macro above. Vectors of Arrays the size of a bank
    BankType Bank0; //Switchable if in large Cartridge mode
    BankType ROMBanks;
    BankType RAMBanks;

    //Registers storing the values of the ROM/RAM Bank.

    uint8_t ROMBankRegister;
    uint8_t RAMBankRegister;

    //Indices for the Bank vectors
    uint16_t curROMBankIndex;
    uint16_t curRAMBankIndex;
    uint16_t curBank0Index;
    uint16_t maxBank0Index;

    void WriteROMBank(uint8_t value, uint16_t location);
    void WriteRAMBank(uint8_t value, uint16_t location);
    uint8_t ReadROMBank(uint16_t location);
    uint8_t ReadRAMBank(uint16_t location);
    static Region GetRegion(uint16_t location);
public:
    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;
    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;
    void Initialize() override;
    void SwitchBank0(uint16_t number);
    void SwitchROMBank(uint16_t number) override;
    void SwitchRAMBank(uint16_t number) override;
    MBC1(int ROMBankCount, int RAMBankCount);

    void LoadROMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;
    void LoadRAMBank(uint16_t index, std::array<uint8_t, 0x4000> bank) override;

    std::string GetDebugInformation();
};


#endif //GBNEXT_MBC1_H
