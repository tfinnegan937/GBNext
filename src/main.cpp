#include <iostream>
#include "GBNext.h"
#include <chrono>
#include <fstream>
using namespace std;
int main() {
    GBNext app;
    cout << app.LoadROM("/mnt/c/Users/plays/CLionProjects/GBNext/tetris.gb") << endl;
    app.Run();
    return 0;
}
