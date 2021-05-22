//
// Created by tfinnegan on 5/7/21.
//

#include "../include/Memory/VolatileMemory.h"
#include <stdexcept>
#include <iomanip>

#define LOWRAMSTART 0xC000
#define LOWRAMEND 0xCFFF
#define LOWRAMBANKSTART 0xD000
#define LOWRAMBANKEND 0xDFFF
#define ECHOSTART 0xE000
#define ECHOEND 0xFDFF
#define HIGHRAMSTART 0xFF80
#define HIGHRAMEND 0xFFFE

#include <stdexcept>
uint8_t VolatileMemory::ReadAt(uint16_t location) {

    uint16_t index = GetMemoryIndex(location);


    return volMem[index];
}

void VolatileMemory::WriteTo(uint8_t value, uint16_t location) {
    uint16_t index = GetMemoryIndex(location);

    volMem[index] = value;
}

void VolatileMemory::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    for(int i = start; i < end; i++){
        WriteTo(value, i);
    }
}

void VolatileMemory::Initialize() {
    auto it = volMem.begin();
    //Initialize memory to zero
    for(it; it != volMem.end(); it++){
        *it = 0x00;
    }
}

uint16_t VolatileMemory::GetMemoryIndex(uint16_t location) {
    if(location >= LOWRAMSTART && location <= LOWRAMEND){

        return location - LOWRAMSTART; //Low RAM

    }else if(location >= LOWRAMBANKSTART && location <= LOWRAMBANKEND){

        //This branch is a placeholder.
        //For now, it simply references the memory after the first bank.
        //In the future, it will handle the CGB's RAM banks.
        return location - LOWRAMSTART;

    }else if(location >= ECHOSTART && location <= ECHOEND) {

        //This branch is a duplicate of the first branch
        //To account for the RAM echo.
        return location - ECHOSTART;

    }else if(location >= HIGHRAMSTART && location <= HIGHRAMEND){

        return (location - HIGHRAMSTART) + (ECHOEND - LOWRAMSTART); //Shift range to start at end of other RAM

    }else{

        std::stringstream stream;
        stream << std::hex << location;
        throw(std::runtime_error("Memory Indexing Error: Location " + stream.str() + "called in volatile memory."
        + " This value is out of bounds."));

    }
    return 0;
}
