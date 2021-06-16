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
 * which are handled in the Cartridge memory as that exists on-cartridge, and all switchable elements should be handled in a
 * single object. This object is strictly the volatile memory that is always available.
 *
 * IMPORTANT: Though this object does not represent contiguous blocks of memory, this object stores all of those
 * blocks in a single array and then calculates the proper index given that region's position in the array.
 * That is, the range FF80-FFFE is stored contiguously, beginning immediately after the range C000-FDFF. C000 is mapped
 * to index zero.
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
#define VOLMEM_SIZE 0x3E7D

class VolatileMemory : MemoryObject{
private:
    std::array<uint8_t, VOLMEM_SIZE> volMem;
    static uint16_t GetMemoryIndex(uint16_t location);
public:
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;

    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override; //Be careful with this function. If you
                                                             //Try to write from LOWRAM to HIGHRAM
                                                             //It will throw an error as it will
                                                             //try to write to the memory locations in between the
                                                             // spaces.

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;
};


#endif //GBNEXT_VOLATILEMEMORY_H
