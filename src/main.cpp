#include <iostream>
#include "Memory/MemoryMap.h"
int main() {
    MemoryMap mem;
    mem.Initialize();

    mem.WriteRange(0xFF, 0xFF80, 0xFFFF);
    mem.WriteRange(0xFF, 0xC000, 0xDFFF);
    std::cout << endl;
    for(int i = 0; i < 0x10000; i++){
        std::cout << std::hex << i << ": " << (unsigned int) mem.ReadAt(i) << std::endl;
    }
    return 0;
}
