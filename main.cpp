#include "devices.hpp"
#include "mem16.hpp"
#include "core.hpp"
#include <array>
using namespace machina;

int main() {
    mem16 MMD;
    device devX;
    devX.RegisterPortS1(16);
    MMD.RegisterPortS1(4);
    std::array<BusLine , 4> MemoryLane;
    for (auto& line : MemoryLane) {
        Port p;
        p.line = &line;
        MMD.RegisterPortS2(p);
        devX.RegisterPortS2(p);
    }
    devX.Send(0 , 1);
    devX.Send(1 , 0xbeaf);
    devX.Send(2 , 0xdead);
    MMD.tick();
    devX.Send(0 , 2);
    devX.Send(1 , 0xbeaf);
    devX.Send(2 , 0xdead);
    MMD.tick();
    return 0;
}
