//
// Created by plays on 6/15/2021.
//

#include "Memory/ObjectAttributeMemory.h"

uint8_t ObjectAttributeMemory::ReadAt(uint16_t location, bool ppuMode2) {
    if(ppuMode2){
        return ReadRAMBug(location);
    }
    return OAM[location - 0xFE00];
}

void ObjectAttributeMemory::WriteTo(uint8_t value, uint16_t location, bool ppuMode2) {
    if(ppuMode2){
        WriteRAMBug(value, location);
        return;
    }
    OAM[location - 0xFE00] = value;
}

void ObjectAttributeMemory::WriteRange(uint8_t value, uint16_t start, uint16_t end) {
    for(int i = start; i < end; i++){
        WriteTo(value, i);
    }
}

void ObjectAttributeMemory::Initialize() {
    OAM.fill(0x00);
}

ObjectAttributeMemory::OAMRow ObjectAttributeMemory::GetRow(uint16_t location) {
    OAMRow curRow;

    uint8_t wordPosition = (location - 0xFFA0) % 2; // All even bytes are the first byte in a word. This is the word byte index, assuming a word is a byte array with two elements.

    curRow.rowNumber = (location - 0xFFA0) / 20; // Decimal is truncated. There are 20 rows total

    uint8_t wordStartLoc = location; //Assume the word starts here, and adjust it forward if not.

    if(wordPosition != 0){
        wordStartLoc--;
    }

    uint8_t rowPosition = (wordStartLoc - 0xFE00) / 2; //Each word takes two bytes. This will give the index of the word in the row

    curRow.rowAddress = location - (2 * rowPosition); //Take the location address and subtract the number of bytes required to get to row index 0.

    for(int i = curRow.rowAddress; i < curRow.rowAddress + 8; i += 2){ // Start at the start of the row.
        curRow.words[i - curRow.rowAddress] = ((uint16_t)(OAM[i - curRow.rowAddress]) << 8) | OAM[(i - curRow.rowAddress) + 1]; //Get the first and second byte and create a 16-bit integer from them.
    }

    return curRow;
}

ObjectAttributeMemory::OAMRow ObjectAttributeMemory::GetPreviousRow(uint16_t location) {
    return GetRow(location - 8);
}

void ObjectAttributeMemory::WriteRAMBug(uint8_t value, uint16_t location) {
    OAMRow selectedRow = GetRow(location);

    if(selectedRow.rowNumber > 0) { //Sprite RAM bug does not affect the first two tiles
        OAMRow previousRow = GetPreviousRow(selectedRow.rowAddress);

        uint16_t a = selectedRow.words[0];
        uint16_t b = previousRow.words[0];
        uint16_t c = previousRow.words[2];

        selectedRow.words[0] = ((a ^ c) & (b ^ c)) ^ c;

        for (int i = 2; i < 4; i++) {
            selectedRow.words[i] = previousRow.words[i];
        }

        for (int i = 0; i < 8; i++) {
            if (i % 2 == 0) {
                OAM[selectedRow.rowAddress + i] =
                        (selectedRow.words[i / 2] & 0xFF00) >> 8; //Get the first byte of that word
            } else {
                OAM[selectedRow.rowAddress + i] = selectedRow.words[i / 2]; //Get the second byte of that word
            }
        }
    }else{
        OAM[location - 0xFE00] = value;
    }

}

uint8_t ObjectAttributeMemory::ReadRAMBug(uint16_t location) {
    OAMRow selectedRow = GetRow(location);

    if(selectedRow.rowNumber > 0) { //Sprite RAM bug does not affect the first two tiles
        OAMRow previousRow = GetPreviousRow(selectedRow.rowAddress);

        uint16_t a = selectedRow.words[0];
        uint16_t b = previousRow.words[0];
        uint16_t c = previousRow.words[2];

        selectedRow.words[0] = b | (a & c);

        for (int i = 2; i < 4; i++) {
            selectedRow.words[i] = previousRow.words[i];
        }

        for (int i = 0; i < 8; i++) {
            if (i % 2 == 0) {
                OAM[selectedRow.rowAddress + i] =
                        (selectedRow.words[i / 2] & 0xFF00) >> 8; //Get the first byte of that word
            } else {
                OAM[selectedRow.rowAddress + i] = selectedRow.words[i / 2]; //Get the second byte of that word
            }
        }
    }
    return OAM[location];
}
