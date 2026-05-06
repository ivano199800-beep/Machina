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

void core16::tick() {
 
}

