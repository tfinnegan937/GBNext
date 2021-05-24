#include <iostream>
#include "Memory/MBC/MBC1.h"
int main() {
    MBC1 testmbc1(8, 2);
    testmbc1.Initialize();
    testmbc1.WriteTo(0x01, 0x6000);
    testmbc1.WriteTo(0x0A, 0x0000);

    testmbc1.WriteTo(0x01, 0xA000);

    testmbc1.WriteTo(0x01, 0x4000);
    testmbc1.WriteTo(0xFF, 0xA000);

    testmbc1.WriteTo(0x00, 0x4000);

    std::cout << "Banked Value 1: " << std:: hex << (int)testmbc1.ReadAt(0xA000) << std::endl;

    testmbc1.WriteTo(0x01, 0x4000);

    std::cout << "Banked Value 2: " << std:: hex << (int)testmbc1.ReadAt(0xA000) << std::endl;

    testmbc1.WriteTo(0x00, 0x4000);

    std::cout << "Banked Value 1: " << std:: hex << (int)testmbc1.ReadAt(0xA000) << std::endl;


    std::cout << testmbc1.GetDebugInformation();
    //std::cout << std::hex << (int)testmbc1.ReadAt(0xBFFE);
    return 0;
}
