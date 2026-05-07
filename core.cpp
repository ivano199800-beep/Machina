#include "core.hpp"



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
    else if (stage == 1) {
        // fetch the instruction
        HWORD_ fMode = 1; //this->modes[1];
        //std::cout << "fetch mode:" << (unsigned short)fMode << std::endl;
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
    else if (stage == 2) {
        std::cout << "pending " << std::hex << (int)this->modes[2] << std::endl;
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
                this->hiddenReg[2] = this->Receive(9);
                this->modes[3] = 1;
                stage = 3;
            }
        }
    } else if (stage == 3) {
        // execute stage
        //WIP
        std::cout <<
        "WIP: the instruction Register for debugging " << (int)this->hiddenReg[0] << '\n' <<
        "IP = " << (int)this->regx[7] << std::endl;
        INSTR_ instr = this->hiddenReg[0];
        HWORD_ opcode   = (instr >> 11) & 0x1f;
        HWORD_ opmode   = (instr >> 8) & 0x7;
        HWORD_ regB     = (instr >> 5) & 0x7;
        HWORD_ regA     = (instr >> 2) & 0x7;
        HWORD_ rMode    = instr & 0x3;
        std::array<char* , 32> ops {
            "NOP",
            "HLT",
            "JMP",
            "JZE",
            "JOF",
            "JNE",
            "JCA",
            "LDI",
            "LDM",
            "LDR",
            "STR",
            "PSH",    
            "POP",
            "CAL",
            "RET",
            "ADD",
            "SUB",
            "SFT",
            "RCV",
            "SND"
        };
        std::cout << "opcode " << ops[(int)opcode] << '\n' <<
        "opmode " << (int)opmode << '\n' <<
        "regB " << (int)regB << '\n' <<
        "regA " << (int)regA << '\n' <<
        "rMode " <<  (int)rMode << '\n';

        switch ((isa)opcode) {
            case isa::NOP:
                break;
            case isa::HLT:                    
                this->Send(0 , 1);
                this->Send(1 , 1);
                break;
            case isa::ADD:
                this->regx[regB] += this->regx[regA];
                break;
            case isa::SUB:
                this->regx[regB] -= this->regx[regA];
                break;
            case isa::SND:
                this->Send(regx[regB] , regx[regA]);
                break;
            case isa::RCV:
                regx[regA] = this->Receive(regx[regB]);
                break;
            case isa::LDI:
                if (0)//!this->modes[4]) 
                {
                    this->regx[opmode] = ((HWORD_*)&instr)[1];
                    break;
                } else {
                    if (this->modes[3]) {
                        // put the data to the register
                        this->regx[opmode] = this->hiddenReg[2];

                        this->modes[3] = 0;
                        this->modes[2] = 0; 
                    } else {
                        //
                        this->regx[7] += 1;
                        this->hiddenReg[2] = this->regx[7];
                        this->hiddenReg[3] = opmode;
                        this->modes[2] =  2;
                        stage = 4;
                        return;
                    }
                    break;
                }
                break;
            default:
                break;
            }

        this->regx[7]++;
        stage = 1;
        return;
    } else if (stage == 4) {
        // request data;
        auto addr = this->hiddenReg[2];
        auto dest = this->hiddenReg[3];
        this->Send(8 ,2);
        this->Send(9,0);
        this->Send(10 , addr);
        stage = 2;
        this->modes[2] = 2 ;
    }
}


void core16::set(HWORD_ key , HWORD_ value) {
    this->modes[key % 0x20] = value;
    return;
} 

