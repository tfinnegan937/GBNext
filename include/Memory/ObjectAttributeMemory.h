//
// Created by plays on 6/15/2021.
//

#ifndef GBNEXT_OBJECTATTRIBUTEMEMORY_H
#define GBNEXT_OBJECTATTRIBUTEMEMORY_H

#include "MemoryObject.h"
#include <array>
using namespace std;
class ObjectAttributeMemory : public MemoryObject{
private:
     typedef struct OAMRow{
         uint16_t rowAddress;
         uint16_t words[4];
     } OAMRow;


     array<uint8_t, 0xFF> OAM;
     OAMRow GetRow(uint16_t location);
     OAMRow GetPreviousRow(uint16_t location);
public:
    uint8_t ReadAt(uint16_t location) override;

    void WriteTo(uint8_t value, uint16_t location) override;

    void WriteRange(uint8_t value, uint16_t start, uint16_t end) override;

    void Initialize() override;

    void WriteRAMBug(uint8_t value, uint16_t location);
    uint8_t ReadRAMBug(uint16_t location);

};


#endif //GBNEXT_OBJECTATTRIBUTEMEMORY_H
