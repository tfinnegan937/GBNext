//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_IOPORTS_H
#define GBNEXT_IOPORTS_H
#include "MemoryObject.h"

class IOPorts : MemoryObject{
public:
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;

    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;
};


#endif //GBNEXT_IOPORTS_H
