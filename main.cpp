#include "devices.hpp"
#include "mem16.hpp"
#include "core.hpp"
#include <array>
#include <cstdlib>
using namespace machina;

int main() {
    mem16 mem;
    core16 core;
    std::array<BusLine , 4> lanes;
    // Bind Bus
    core.RegisterPortS1(8);
    mem.RegisterPortS1(8);

    for (auto& line : lanes) {
        Port p;
        p.line = &line;
        core.RegisterPortS2(p);
        mem.RegisterPortS2(p);
    }
    for (int s = 0 ; s < 64 ; s++) {
        core.Send(0 , 0x1);
        core.Send(1 , std::rand());
        core.Send(2 , std::rand() % 256);
        mem.tick();
    }
    for (int s = 0 ; s < 64 ; s++) {
        core.Send(0 , 0x2);
        core.Send(2 , std::rand() % 256);
        mem.tick();
    }
    return 0;
}
