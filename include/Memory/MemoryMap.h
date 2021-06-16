//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_MEMORYMAP_H
#define GBNEXT_MEMORYMAP_H
#include <memory>
#include <fstream>
#include "MemoryObject.h"
#include "Cartridge.h"
#include "VolatileMemory.h"
#include "VideoRAM.h"
#include "IOPorts.h"
#include "ObjectAttributeMemory.h"
using namespace std;


class MemoryMap : MemoryObject{
private:

    enum MemoryType{ //For selecting the correct memory object
        TypeVolatile, //All RAM aside from cartridge RAM
        TypeCartridge, //Cartridge, switchable Cartridge banks, and switchable RAM banks
        TypeIO, //I/O ports
        TypeVideo, //VRAM. Similar to TypeVolatile, but has protections based on HBlank and VBlank
        TypeSprite, //Sprite memory. Similar to TypeVolatile, but split into such a way as to identify each individual sprite
        TypeInterrupt, //One 8-bit register at the top of memory.
        TypeEmpty //No memory is mapped to this range. This exists to make the code more readable.
    };

    //See the GetMemoryObject and ReadAt functions to see how these are mapped to the machine's actual memory map.
    shared_ptr<VolatileMemory> mainMemory;
    shared_ptr<Cartridge> cartridge;
    shared_ptr<IOPorts> ioPorts;
    shared_ptr<VideoRAM> vRAM;
    shared_ptr<ObjectAttributeMemory> OAM;
    //helper functions
    static MemoryType GetMemoryObject(uint16_t location);

public:
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;

    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    void LoadRom(ifstream *file);
    MemoryMap();
};


#endif //GBNEXT_MEMORYMAP_H
