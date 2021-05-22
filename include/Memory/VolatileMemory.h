//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_VOLATILEMEMORY_H
#define GBNEXT_VOLATILEMEMORY_H
#include "MemoryObject.h"
#include <array>
/*
 * VolatileMemory
 *-----------------------
 * This is a memory object for handling the Game Boy's internal RAM. This does not include the switchable RAM banks,
 * which are handled in the ROM memory as that exists on-cartridge, and all switchable elements should be handled in a
 * single object. This object is strictly the volatile memory that is always available.
 *
 * Memory locations:
 *
 * Internal RAM space 1: C000 - DFFF
 * Echo of Interal RAM (Exact Copy of Space 1 ranged C000-DDFF): E000 - FDFF
 * Internal RAM space 2: FF80 - FFFE
 *
 * Rather than having an entire memory space that echoes the internal RAM, reads and writes to that space
 * will access the same Array.
 *
 * When Color Game Boy is implemented the range D000 - DFFF will become switchable RAM banks.
 */
#define VOLMEMSIZE 0x3E7D

class VolatileMemory : MemoryObject{
private:
    std::array<uint8_t, VOLMEMSIZE> volMem;
    uint16_t GetMemoryIndex(uint16_t location);
public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;
};


#endif //GBNEXT_VOLATILEMEMORY_H
