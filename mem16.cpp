#include "mem16.hpp"




using namespace machina;

void mem16::tick() {
    WORD_ mode = this->Receive(0);
    WORD_ data = this->Receive(1);
    WORD_ addr = this->Receive(2);
    if      (!mode) return;
    else if (mode == 1) {
        //write
        this->data[addr] = data;
        std::cout << "written " <<  std::hex << data << " at [" << std::hex << addr<< "]\n";
    } else if (mode == 2) {
        this->Send(1 , this->data[addr]);
        std::cout << "read " <<  std::hex << this->data[addr] << " at [" << std::hex << addr<< "]\n";
    } else {
        std::cout << "mem16 WIP" << '\n';
    }
    
}

void mem16::start() {}