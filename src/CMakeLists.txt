# cmake_minimum_required(VERSION <specify CMake version here>)
project(GBNext)
cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
add_executable(GBNext main.cpp GBNext.cpp MemoryObject.cpp VolatileMemory.cpp Cartridge.cpp MemoryMap.cpp IOPorts.cpp ../include/Memory/IOPorts.h MemoryBankController.cpp ../include/Memory/MBC/MemoryBankController.h ../include/Memory/MBC/MBC1.cpp ../include/Memory/MBC/MBC1.h)
target_include_directories(GBNext PRIVATE ../include)
