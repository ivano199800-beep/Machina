#include "core.hpp"


using namespace machina;

static WORD_ memoryReg = 0;
static WORD_ instr = 0;
static HWORD_ iMode = 0;
void core16::tick() {
    // port 0 to 7 is for the board
    if (!state) {
        if (this->Receive( 0 )) state = 1;
        return;
    }
    if (state == 1) {
        this->Send(0x8 , 2);
        this->Send(0x9 , 0);
        this->Send(0xa , this->regx[7]);
        this->Send(0xb , 0);
        iMode = 0;
        state = 3;
    } else if (state == 2) {
        if (iMode) {
            
        } else if (iMode == 1) {
            instr = memoryReg;
            HWORD_ opcode   = (instr >> 11) & 0x1f;
            HWORD_ opmode   = (instr >> 8) & 0x7;
            HWORD_ regB     = (instr >> 5) & 0x7;
            HWORD_ regA     = (instr >> 2) & 0x3;
            HWORD_ rMode    = instr & 0x3;
            
            switch ((isa)opcode) {
                case isa::NOP:
                    break;
                case isa::HLT:                    
                    this->Send(0 , 1);
                    this->Send(1 , 1);
                    break;
                default:
                    break;
            }
            this->regx[7]++;
        }
    } else if (state == 3) {
            if (this->Receive(0xb)) {
                memoryReg = this->Receive(0x9);
                state = 2;
            } else return;
    }
}

