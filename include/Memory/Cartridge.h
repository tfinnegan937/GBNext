//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_CARTRIDGE_H
#define GBNEXT_CARTRIDGE_H
#include "MemoryObject.h"

class Cartridge : MemoryObject{
public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;
};


#endif //GBNEXT_CARTRIDGE_H
