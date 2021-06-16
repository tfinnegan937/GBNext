//
// Created by plays on 6/15/2021.
//

#include <cstdint>
#include "Memory/VideoRAM.h"

uint8_t VideoRAM::ReadAt(uint16_t location, bool ppuMode2) {
    if(location < 0x8000 || location > 0x9FFF){
        throw(runtime_error("Error: VRAM object received read call outside of its range"));
    }
    return VRAM[location - 0x8000];
}

void VideoRAM::WriteTo(uint8_t value, uint16_t location, bool ppuMode2) {
    if(location < 0x8000 || location > 0x9FFF){
        throw(runtime_error("Error: VRAM object received read call outside of its range"));
    }
    VRAM[location - 0x8000] = value;
}

void VideoRAM::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    for(int i = start; i < end; i++){
        VRAM[i - 0x8000] = value;
    }
}

void VideoRAM::Initialize() {
    VRAM.fill(0x00);
}
