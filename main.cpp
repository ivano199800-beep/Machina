#include "Device.hpp"
#include <array>
using namespace machina;

int main() {
    std::array<BusLine , 8> MainLine;
    std::array<uint16_t , 256> Memory; // 256 for now so i dont blow up my terminal
    Device Ram;
    Ram.RegisterPortS1(8);
    for (auto& Line : MainLine) {
        Port p;
        p.line = &Line;
        Ram.RegisterPortS2(p);
    }
    Device devX;
    devX.RegisterPortS1(8);
    for (auto& Line : MainLine) {
        Port p;
        p.line = &Line;
        devX.RegisterPortS2(p);
    }
    devX.tick();
    devX.Send(0 , 64);
    devX.Send(1 , 420);

    Ram.tick();
    uint16_t address = Ram.Receive(0);
    uint16_t data = Ram.Receive(1);
    Memory[address] = data;

    int i = 0;
    for (auto& s : Memory) {
        std::cout << std::hex << s;
        if (i < 16) {
            std::cout << '\n';
            i = -1;
        }
        i++;
    }
    return 0;
}
