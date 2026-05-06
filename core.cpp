#include "core.hpp"


using namespace machina;

static WORD_ memoryReg = 0;
static WORD_ instr = 0;
static HWORD_ iMode = 0;
void core::tick() {
    // port 0 to 7 is for the board
    if (!state) {
        // tell the board its idle
        this->Send(0 , 0);
        this->Send(1 , 1);
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
            WORD_ opcode = ((HWORD_)instr) << 4;
            WORD_ opmode = ((HWORD_)instr) & 0xf;
            WORD_ rMode  = *((HWORD_*)(&instr)[1]) & 3;
            WORD_ regA   = (*((HWORD_*)(&instr)[1]) >> 2) & 7;
            WORD_ regB   = (*((HWORD_*)(&instr)[1]) >> 5) & 7;
            
            switch (opcode) {

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

