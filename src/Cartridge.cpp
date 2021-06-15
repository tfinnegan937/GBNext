//
// Created by tfinnegan on 5/7/21.
//

#include "../include/Memory/Cartridge.h"
#include <memory>
#include <string>
#include <cmath>
#include <iostream>
uint8_t Cartridge::ReadAt(uint16_t location) {
    return controller->ReadAt(location);
}

void Cartridge::WriteTo(uint8_t value, uint16_t location) {
    controller->WriteTo(value, location);
}

void Cartridge::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    controller->WriteRange(value, start, end);
}

void Cartridge::Initialize() {
    ColorGB = false;
}


void Cartridge::LoadROM(uint8_t * arr, int val) {
    //Mapped according to the table at https://gbdev.io/pandocs/The_Cartridge_Header.html
    uint8_t cartType = 0x00;

    if(val < 0x8000){
        throw (std::runtime_error("Byte Array too small to be complete cart."));
    }
    cartType = arr[0x147];

    SelectBankType(cartType);

    uint8_t CGB_descriptor = arr[0143];
    //TODO Handle CGB descriptor

    //TODO collect and handle SGB descriptor

    //Handle ROM Size
    uint8_t ROMSize_descriptor = arr[0x148];
    SelectROMSize(ROMSize_descriptor);

    //Handle RAM Size
    uint8_t RAMSize_descriptor = arr[0x149];
    SelectRAMSize(RAMSize_descriptor);

    //Select and initialize the correct MBC class
    CreateControllerObject();
    controller->Initialize();

    //Load the ROM array into the controller class
    for(int offset = 0x0000; offset < (0x4000 * ROMSize); offset+= 0x4000){ //Get each bank
        std::array<uint8_t, 0x4000> bank{};
        for(int memLoc = offset; memLoc < (offset + 0x4000); memLoc++){ //Load memory from specific bank into object
            bank[memLoc - offset] = arr[offset + memLoc]; //Store the element of the array into a bank object
        }
        controller->LoadROMBank(offset / 0x4000, bank); //Store the bank at the appropriate index
    }

    //TODO handle RAM save loading




}

void Cartridge::SelectBankType(uint8_t descriptor) {
    switch(descriptor){
        case 0x00:
            bankType = MemoryBankController::ROMOnly;
            break;
        case 0x01:
            bankType = MemoryBankController::MBC1;
            break;
        case 0x02:
            bankType = MemoryBankController::MBC1Ram;
            break;
        case 0x03:
            bankType = MemoryBankController::MBC1RamBat;
            break;
        case 0x05:
            bankType = MemoryBankController::MBC2;
            break;
        case 0x06:
            bankType = MemoryBankController::MBC2Bat;
            break;
        default:
            throw(std::runtime_error("This cartridge type is currently unsupported"));
            //TODO implement additional bank types
    }
}

void Cartridge::SelectROMSize(uint8_t descriptor) {
    if(descriptor > 0x08){
        throw(std::runtime_error("Error: Invalid ROM size descriptor"));
    }

    ROMSize = std::pow(2, descriptor + 1); //Descriptor 0x00 is 2. From there it goes up by powers of 2
                                                 //I.E. 0x01 = 4 banks, 0x02 = 8 banks, 0x03 = 16 banks
                                                 //The pattern indicates that the number of banks available
                                                 //is equal to 2^(descriptor + 1)
}

void Cartridge::SelectRAMSize(uint8_t descriptor) {
    switch(descriptor){
        case 0x00:
            RAMSize = 0;
            break;
        case 0x01: //Unused. Handling to no RAM instead of a crash
            RAMSize = 0;
            break;
        case 0x02:
            RAMSize = 1;
            break;
        case 0x03:
            RAMSize = 4;
            break;
        case 0x04:
            RAMSize = 16;
            break;
        case 0x05:
            RAMSize = 8; //Not a mistake. RAM Size to descriptor does not seem to be mapped in order.
            break;
        default:
            throw(std::runtime_error("Error: Invalid RAM size descriptor"));
    }
}

void Cartridge::CreateControllerObject() {
    switch(bankType){
        case MemoryBankController::ROMOnly:
            controller = std::make_unique<NoMBC>(ROMSize, RAMSize);
            break;
        case MemoryBankController::MBC1:
            controller = std::make_unique<MBC1>(ROMSize, 0);
            break;
        case MemoryBankController::MBC1Ram:
            controller = std::make_unique<MBC1>(ROMSize, RAMSize);
            break;
        case MemoryBankController::MBC1RamBat:
            controller = std::make_unique<MBC1>(ROMSize, RAMSize); //TODO handle battery saves
            break;
        case MemoryBankController::MBC2:
            controller = std::make_unique<MBC2>(ROMSize);
            break;
        case MemoryBankController::MBC2Bat:
            controller = std::make_unique<MBC2>(ROMSize); //TODO handle battery saves
            break;
        default:
            throw std::runtime_error("Error: Current MBC type is not yet supported");
    }
}
