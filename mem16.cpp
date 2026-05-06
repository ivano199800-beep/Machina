#include "mem16.hpp"




using namespace machina;

void mem16::tick() {
    std::cout << "at lane: " << std::hex << (this->lane) << '\n';   
    WORD_ mode = this->Receive(this->lane + 0);
    WORD_ data = this->Receive(this->lane + 1);
    WORD_ addr = this->Receive(this->lane + 2);
    if      (!mode) return;
    
    else if (mode == 1) {
        //write
        this->data[addr] = data;
        std::cout << "written " <<  std::hex << data << " to [" << std::hex << addr<< "]\n";
    } else if (mode == 2) {
        this->Send(1 , this->data[addr]);
        std::cout << "read " <<  std::hex << this->data[addr] << " from  [" << std::hex << addr<< "]\n";
    } else {
        std::cout << "mem16 WIP" << '\n';
    }
    
}

void mem16::start() 
{
    std::cout << "mem16 WIP" << '\n';
}