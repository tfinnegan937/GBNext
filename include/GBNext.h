//
// Created by tfinnegan on 5/7/21.
//

#ifndef GBNEXT_GBNEXT_H
#define GBNEXT_GBNEXT_H
#include "Memory/MemoryMap.h"
#include "CPU/CPU.h"
#include <memory>
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std;
using namespace chrono;

class GBNext {
public:
    enum EmulatorState{
        NoROM,
        ROMLoaded,
        Halted,
        Running,
        Paused,
    };
private:
    //State Variables
    EmulatorState state;
    //FilePaths
    ifstream currentROM;

    //Hardware Components
    shared_ptr<MemoryMap> memory;

    unique_ptr<CPU> cpu;

    //Timer ticks
    microseconds deltaTimeM; //Time since start of last machine cycle
    microseconds deltaTime; //Time since start of frame
    microseconds time; //Accumulated time since Run was called in milliseconds

    //Helper Functions
    static microseconds getUnixTimeMicroseconds() ;
    //Tick Functions
    void cpuTick(int &cycles); //One full instruction execution
    void Tick(); //One full frame
public:
    GBNext();
    bool LoadROM(const string& romPath);
    void Run();

};


#endif //GBNEXT_GBNEXT_H
