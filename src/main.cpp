#include <iostream>
#include "Memory/MBC/MBC1.h"
#include "Memory/MemoryMap.h"
#include <fstream>
int main() {
    MemoryMap map;
    map.Initialize();

    ifstream file;

    try {
        file.open("/mnt/c/Users/plays/CLionProjects/GBNext/tetris.gb", ios::binary);
    }catch(std::exception & e){
        std::cout << e.what();
    }

    map.LoadRom(&file);
    return 0;
}
