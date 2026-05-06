#include "core.hpp"

            // HWORD_ opcode   = (instr >> 11) & 0x1f;
            // HWORD_ opmode   = (instr >> 8) & 0x7;
            // HWORD_ regB     = (instr >> 5) & 0x7;
            // HWORD_ regA     = (instr >> 2) & 0x7;
            // HWORD_ rMode    = instr & 0x3;


            //  switch ((isa)opcode) {
            //     case isa::NOP:
            //         break;
            //     case isa::HLT:                    
            //         this->Send(0 , 1);
            //         this->Send(1 , 1);
            //         break;
            //     case isa::ADD:
            //         this->regx[regB] += this->regx[regB];
            //         break;
            //     case isa::SUB:
            //         this->regx[regB] -= this->regx[regB];
            //         break;
            //     case isa::SND:
            //         this->Send(regx[regB] , regx[regA]);
            //         break;
            //     case isa::RCV:
            //         regx[regA] = this->Receive(regx[regB]);
            //         break;
            //     default:
            //         break;
            // }
using namespace machina;

void core16::start() {
    std::cout << "CORE WIP" << std::endl;
}
void core16::tick() {
    auto& stage = modes[0];
    if (stage == 0) { 
        if (this->Receive(1)) return;
        stage = 1;
        return;
    }
    if (stage == 1) {
        // fetch the instruction
        HWORD_ fMode = this->modes[1];
        std::cout << "fetch mode:" << fMode << std::endl;
        if (fMode == 0) {
            // Direct Instruction Feed
            this->hiddenReg[0] = this->Receive(2);
            stage = 3; 
        } else {
            this->Send(0x8 , 2);
            this->Send(0x9 , 0);
            this->Send(0xa , this->regx[7]);
            stage = 2;
            this->modes[2] = 1;
        }
    }
    if (stage == 2) {
        std::cout << "pending" << std::hex << this->modes[2] << std::endl;
        if (this->modes[2] == 1) {
            if (this->Receive(8) == 2) {
                return;
            } else {
                this->hiddenReg[0] = this->Receive(9);
                this->modes[3] = 0;
                stage = 3;
            }
        } else if (modes[2] == 2) {
            if (this->Receive(8) == 2) {
                return;
            } else {
                this->hiddenReg[1] = this->Receive(9);
                this->modes[3] = 1;
                stage = 3;
            }
        }
    } else if (stage == 3) {
        // execute stage
        //WIP
        std::cout <<
        "WIP: the instruction Register for debugging " <<
        std::hex << this->hiddenReg[0] <<
        "\nIP = " << this->regx[7] <<
        std::endl;
        this->regx[7]++;
        stage = 1;
        return;
    } 
}


void core16::set(WORD_ key , HWORD_ value) {
    switch (key) {
        case 0:
            this->modes[1] = value;
            break;
        default:
            break;
    }
} 

