//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_VOLATILEMEMORY_H
#define GBNEXT_VOLATILEMEMORY_H
#include "MemoryObject.h"

class VolatileMemory : MemoryObject{
private:
public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;
};


#endif //GBNEXT_VOLATILEMEMORY_H
