//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_MEMORYMAP_H
#define GBNEXT_MEMORYMAP_H
#include <memory>
#include "MemoryObject.h"
#include "ROM.h"
#include "VolatileMemory.h"
#include "IOPorts.h"

using namespace std;


class MemoryMap : MemoryObject{
private:

    enum MemoryType{ //For selecting the correct memory object
        TypeVolatile,
        TypeROM,
        TypeIO,
        TypeVideo,
        TypeSprite,
        TypeInterrupt,
        TypeEmpty
    };

    shared_ptr<VolatileMemory> mainMemory;
    shared_ptr<ROM> rom;
    shared_ptr<IOPorts> ioPorts;
    //helper functions
    static MemoryType GetMemoryObject(uint16_t location);

public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    MemoryMap();
};


#endif //GBNEXT_MEMORYMAP_H
