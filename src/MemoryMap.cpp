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

}

void MemoryMap::WriteRange(uint8_t value, uint16_t start, uint16_t end) {

}

void MemoryMap::Initialize() {

}

MemoryMap::MemoryType MemoryMap::GetMemoryObject(uint16_t location) {
    if(location < 0x8000){
        return TypeROM;
    }else if(location < 0xA000){
        return TypeVideo;
    }else if(location < 0xFE00){
        return TypeVolatile;
    }else if(location < 0xFEA0){
        return TypeSprite;
    }else if(location < 0xFF00){
        return TypeEmpty;
    }else if(location < 0xFF4C){
        return TypeIO;
    }else if (location < 0xFF80){
        return TypeEmpty;
    }else if (location < 0xFFFF){
        return TypeVolatile;
    }else{
        return TypeInterrupt;
    }
}
