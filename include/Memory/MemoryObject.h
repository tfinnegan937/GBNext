//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_MEMORYOBJECT_H
#define GBNEXT_MEMORYOBJECT_H

#include <cstdint>
class MemoryObject {
public:
    virtual uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) = 0;
    virtual void WriteTo(uint8_t value, uint16_t location, bool ppuMode2) = 0;
    virtual void WriteRange(uint8_t value, uint16_t start, uint16_t end) = 0;
    virtual void Initialize() = 0;
};


#endif //GBNEXT_MEMORYOBJECT_H
