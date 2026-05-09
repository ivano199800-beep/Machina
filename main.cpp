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
    devX.RegisterDID(std::string("devX"));
    core.RegisterDID(std::string("core"));
    mem.RegisterDID(std::string("Memory"));
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

    std::array<INSTR_ , 16> program = {
        core.assemble((HWORD_)core16::isa::LDI , 0, 4, 0, 0),
        7,
        core.assemble((HWORD_)core16::isa::LDI , 0, 1, 0, 0),
        10,
        core.assemble((HWORD_)core16::isa::LDI , 0, 0, 0, 0),
        1,
        core.assemble((HWORD_)core16::isa::LDI , 0, 3, 0, 0),
        0,
        core.assemble((HWORD_)core16::isa::SUB , 0, 1, 0 ,0),
        core.assemble((HWORD_)core16::isa::SND , 1, 4, 1 ,0),
        core.assemble((HWORD_)core16::isa::CMP , 0 , 3 , 1 , 0),
        core.assemble((HWORD_)core16::isa::JNE, 1, 7, 7, 0),
        core.assemble((HWORD_)core16::isa::HLT , 0, 0, 0, 0)
    };


    int i = 0;
    for (auto& s : program) {
        mem.Send(0, 1);
        mem.Send(1, s);
        mem.Send(2 , i);
        mem.tick();
        i++;
    }
    core.set(4 , 0);
    core.set(1 , 1);
    devX.Send(1, 1); // start the core
    std::cout << "-------------loop starts here" <<  std::endl;
    for (int i = 0 ; i <15 * 5 ; i++) {
        core.tick();
        mem.tick();
        //std::cout << "devX Signal: " << (int)devX.Receive(7) << std::endl;
        if (!devX.Receive(1)) break; 
    }
    
    return 0;
}
