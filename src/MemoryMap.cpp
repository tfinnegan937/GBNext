//
// Created by tfinnegan on 5/7/21.
//

#include "../include/Memory/MemoryMap.h"

uint8_t MemoryMap::ReadAt(uint16_t location) {
    MemoryType type = GetMemoryObject(location);
    uint8_t readValue;

    //TODO Lock the map
    switch(type){
        case TypeROM:
            readValue = rom->ReadAt(location);
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
            readValue = ioPorts->ReadAt(location);
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
        case TypeROM:
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
        return TypeROM; //Actual ROM memory
    }else if(location < 0xA000) {
        return TypeVideo; //VRAM
    }else if(location < 0xC000){
        return TypeROM; //Switchable RAM bank. Handled in ROM
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
    mainMemory.reset(new VolatileMemory());
}
