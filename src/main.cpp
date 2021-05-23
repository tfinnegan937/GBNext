#include <iostream>
#include "Memory/MBC/MBC1.h"
int main() {
    MBC1 testmbc1(96, 8);
    testmbc1.Initialize();
    testmbc1.WriteTo(0x01, 0x6000);
    testmbc1.WriteTo(0x60, 0x2000);
    testmbc1.WriteTo(0x03, 0x4000);
    std::cout << testmbc1.GetDebugInformation();
    return 0;
}
