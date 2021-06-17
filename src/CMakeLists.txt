# cmake_minimum_required(VERSION <specify CMake version here>)
project(GBNext)
cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
add_executable(GBNext main.cpp GBNext.cpp MemoryObject.cpp VolatileMemory.cpp Cartridge.cpp MemoryMap.cpp IOPorts.cpp ../include/Memory/IOPorts.h MemoryBankController.cpp ../include/Memory/MBC/MemoryBankController.h MBC1.cpp ../include/Memory/MBC/MBC1.h MBC2.cpp ../include/Memory/MBC/MBC2.h NoMBC.cpp ../include/Memory/MBC/NoMBC.h MBC3.cpp ../include/Memory/MBC/MBC3.h VideoRAM.cpp ../include/Memory/VideoRAM.h ObjectAttributeMemory.cpp ../include/Memory/ObjectAttributeMemory.h CPU.cpp ../include/CPU/CPU.h RegisterUnion.cpp ../include/CPU/RegisterUnion.h)
target_include_directories(GBNext PRIVATE ../include)
