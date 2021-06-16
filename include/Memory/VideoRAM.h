//
// Created by plays on 6/15/2021.
//

#ifndef GBNEXT_VIDEORAM_H
#define GBNEXT_VIDEORAM_H
#include <memory>
#include "MemoryObject.h"

using namespace std;

class VideoRAM : public MemoryObject{
private:
    array<uint8_t, 0x2000> VRAM;
public:
    uint8_t ReadAt(uint16_t location, bool ppuMode2 = false) override;

    void WriteTo(uint8_t value, uint16_t location, bool ppuMode2 = false) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    //TODO add tile and metric collection functions
};


#endif //GBNEXT_VIDEORAM_H
