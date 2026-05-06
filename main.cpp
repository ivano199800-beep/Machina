#include "devices.hpp"
#include "mem16.hpp"
#include "core.hpp"
#include <array>
#include <cstdlib>
using namespace machina;

int main() {
    mem16 mem;
    core16 core;
    std::array<BusLine , 32> lanes;
    // Bind Bus
    device devX;
    devX.RegisterPortS1(16);
    core.RegisterPortS1(16);
    mem.RegisterPortS1(4);
    for (int i = 0 ; i < 8 ; i++) {
        auto& line = lanes[i];
        Port p;
        p.line = &line;
        devX.RegisterPortS2(p);
        core.RegisterPortS2(p);
    }
    for (int i = 8 ; i < 8 + 4 ; i++) {
        auto& line = lanes[i];
        Port p;
        p.line = &line;
        mem.RegisterPortS2(p);
        core.RegisterPortS2(p);
    }
    // do something
    for (int i = 0 ; i < 32 ; i++ ) {
        mem.Send(0,1);
        mem.Send(1,0xbeaf - i);
        mem.Send(2,i);
        mem.tick();
    }
    core.set(0 , 0);
    devX.Send(1, 0); // start the core
    for (int i = 0 ; i < 32 ; i++) {
        core.tick();
        mem.tick();
    }
    return 0;
}
