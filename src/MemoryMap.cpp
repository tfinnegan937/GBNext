//
// Created by tfinnegan on 5/7/21.
//

#include "../include/Memory/MemoryMap.h"
#include <iostream>
uint8_t MemoryMap::ReadAt(uint16_t location) {
    MemoryType type = GetMemoryObject(location);
    uint8_t readValue;

    //TODO Lock the map
    switch(type){
        case TypeCartridge:
            //readValue = rom->ReadAt(location);
            readValue = 0x0000;
            break;
        case TypeVideo:
            //TODO Return the read value
            readValue = 0x0000;
            break;
        case TypeEmpty:
            readValue = 0x0000;
            break;
        case TypeInterrupt:
            //TODO Return interrupt register
            readValue = 0x0000;
            break;
        case TypeSprite:
            //TODO Return value of sprite memory location
            readValue = 0x0000;
            break;
        case TypeIO:
            //readValue = ioPorts->ReadAt(location);
            readValue = 0x0000;
            break;
        case TypeVolatile:
            readValue = mainMemory->ReadAt(location);
            break;
    }

    //TODO unlock the map
    return readValue;
}

void MemoryMap::WriteTo(uint8_t value, uint16_t location) {
    MemoryType type = GetMemoryObject(location);

    //TODO Lock the map
    switch(type){
        case TypeCartridge:
            rom->WriteTo(value, location);
            break;
        case TypeVideo:
            //TODO Return the read value
            break;
        case TypeEmpty:
            //Do nothing
            break;
        case TypeInterrupt:
            //TODO Return interrupt register
            break;
        case TypeSprite:
            //TODO Return value of sprite memory location
            break;
        case TypeIO:
            ioPorts->WriteTo(value, location);
            break;
        case TypeVolatile:
            mainMemory->WriteTo(value, location);
            break;
    }
}
//Used for zeroing out spaces of memory
void MemoryMap::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    for(int i = start; i < end; i++){
        WriteTo(value, i);
    }
}

void MemoryMap::Initialize() {
    mainMemory->Initialize();
}

MemoryMap::MemoryType MemoryMap::GetMemoryObject(uint16_t location) {
    if(location < 0x8000){
        return TypeCartridge; //Actual Cartridge memory
    }else if(location < 0xA000) {
        return TypeVideo; //VRAM
    }else if(location < 0xC000){
        return TypeCartridge; //Switchable RAM bank. Handled in Cartridge
    }else if(location < 0xFE00){
        return TypeVolatile; //Internal RAM + Echo
    }else if(location < 0xFEA0){
        return TypeSprite; //Sprite attribute memory
    }else if(location < 0xFF00){
        return TypeEmpty; //Empty and unusable
    }else if(location < 0xFF4C){
        return TypeIO; //Serial IO ports
    }else if (location < 0xFF80){
        return TypeEmpty; //Empty and unusable
    }else if (location < 0xFFFF){
        return TypeVolatile; //Additional Internal RAM
    }else{
        return TypeInterrupt; //Interrupt Register
    }
}

MemoryMap::MemoryMap() {
    mainMemory = std::make_shared<VolatileMemory>();
}

void MemoryMap::LoadRom(ifstream *file) {

    //Check if file is open, otherwise error
    if(!(file->is_open())){
        throw(std::runtime_error("ROM file has not been opened."));
    }

    //Load file into byte array

    file->seekg(0, ios::end); //Find size of file
    auto fileSize = file->tellg(); //Save size of file
    file->seekg(0, ios::beg); //Return position to start of file
    auto fileArray = std::make_shared<uint8_t[]>(fileSize);
    std::cout << "\n";//Without this line, the program crashes
    file->read((char*)fileArray.get(), fileSize); //Copy the file into the new array

    //These bites are in every cartridge. Check against them to check if the file is a cartridge
    //They represent the nintendo logo
    uint8_t nintendoHeader[] = {
            0xCE,
            0xED,
            0x66,
            0x66,
            0xCC,
            0x0D,
            0x00,
            0x0B,
            0x03,
            0x73,
            0x00,
            0x83,
            0x00,
            0x0C,
            0x00,
            0x0D,
            0x00,
            0x08,
            0x11,
            0x1F,
            0x88,
            0x89,
            0x00,
            0x0E,
            0xDC,
            0xCC,
            0x6E,
            0xE6,
            0xDD,
            0xDD,
            0xD9,
            0x99,
            0xBB,
            0xBB,
            0x67,
            0x63,
            0x6E,
            0x0E,
            0xEC,
            0xCC,
            0xDD,
            0xDC,
            0x99,
            0x9F,
            0xBB,
            0xB9,
            0x33,
            0x3E
    };

    uint8_t headerBytes = 0x30; //The number of bytes in the logo
    uint16_t cartridgeHeaderOffset = 0x104; //The start point of the nintendo logo bytes in the cartridge
    for(int i = 0; i < headerBytes; i++){
        if(fileArray[i + cartridgeHeaderOffset] != nintendoHeader[i]){
            throw(std::runtime_error("Error: The file provided is not a valid GB or GBC cartridge"));
        }
    }

    //TODO pass byte array to Cartridge memory
}
