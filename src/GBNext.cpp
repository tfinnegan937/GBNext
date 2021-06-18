//
// Created by tfinnegan on 5/7/21.
//

#include "../include/GBNext.h"

GBNext::GBNext() {
    memory = make_shared<MemoryMap>();
    memory->Initialize();
    deltaTime = microseconds(0);
    deltaTimeM = microseconds(0);
    time = microseconds(0);
    state = EmulatorState::NoROM;
    cpu = std::make_unique<CPU>(memory);
}

void GBNext::cpuTick(int &cycles) {
    microseconds cycleStart = getUnixTimeMicroseconds();

    //Do Stuff
    memory->Tick(deltaTimeM);
    //Tick CPU
    //NOTE: The CPU decrements the number of cycles
    //as each instruction uses more than one cycle
    cpu->Tick(cycles);

    microseconds cycleEnd = getUnixTimeMicroseconds();

    deltaTimeM = cycleEnd - cycleStart;
}

void GBNext::Tick() {
    microseconds frameStart = getUnixTimeMicroseconds();

    int cycles = 69905; //Number of cycles per frame

    while(cycles > 0){ //Tick until approximately this many cycles are completed (This Emulator is not necessarily cycle accurate)
        cpuTick(cycles);
    }

    microseconds frameEnd = getUnixTimeMicroseconds();

    deltaTime = frameEnd - frameStart; //Used for general emulator timekeeping purposes
    time += deltaTime;
}

microseconds GBNext::getUnixTimeMicroseconds() {
    return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
}

bool GBNext::LoadROM(const string& romPath) {

    try{
        currentROM.open(romPath);
        memory->LoadROM(&currentROM);
    }catch(exception & e){
        cout << e.what() << endl;
        return false;
    }
    state = EmulatorState::ROMLoaded;
    return true;
}

void GBNext::Run() {

    if(state == EmulatorState::ROMLoaded){
        state = EmulatorState::Running;
        time = milliseconds(0);
    }

    while(state == EmulatorState::Running){
        Tick();
    }

}
