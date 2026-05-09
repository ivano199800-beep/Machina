#include "core.hpp"



using namespace machina;

void core16::start() {
    std::cout << "CORE WIP" << std::endl;
}
void core16::tick() {
    auto& stage = modes[0];
    if (stage == 0) { 
        //std::cout << "halted" << std::endl;
        if (!this->Receive(1)) return;
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
        //std::cout << "pending " << std::hex << (int)this->modes[2] << std::endl;
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
    } 
else if (stage == 3) {
        // execute stage
        //WIP
        //std::cout <<
        //"WIP: the instruction Register for debugging " << (int)this->hiddenReg[0] << '\n' <<
        //"IP = " << (int)this->regx[7] << std::endl;
        INSTR_ instr = this->hiddenReg[0];
        HWORD_ opcode   = (instr >> 11) & 0x1f;
        HWORD_ opmode   = (instr >> 8) & 0x7;
        HWORD_ regB     = (instr >> 5) & 0x7;
        HWORD_ regA     = (instr >> 2) & 0x7;
        HWORD_ rMode    = instr & 0x3;
        std::array<const char* , 32> ops {
            "NOP", // 1
            "HLT", // 1
            "JMP", // 1
            "JZE", // 1 
            "JEQ", // 1
            "JNE", // 1
            "JLT", // 1
            "JGT", // 1
            "LDI", // 1
            "LDM", // 1
            "LDR", // 1
            "STR", // 1
            "PSH",  
            "POP",
            "CAL",
            "RET",
            "ADD", // 1
            "SUB", // 1
            "CMP", // 1
            "SFT",
            "RCV", // 1
            "SND" // 1
        };
        //std::cout << "opcode " << ops[(int)opcode] << '\n' <<
        //"opmode " << (int)opmode << '\n' <<
        //"regB " << (int)regB << '\n' <<
        //"regA " << (int)regA << '\n' <<
        //"rMode " <<  (int)rMode << '\n';

        switch ((isa)opcode) {
            case isa::NOP:
                break;
            case isa::HLT:                    
                stage = 0;
                this->Send(0 , 1);
                this->Send(1 , 0);
                break;
            case isa::ADD:
                this->regx[regB] += this->regx[regA];
                if (!this->regx[regB]) this->regx[5] |= 1;
                break;
            case isa::SUB:
                this->regx[regB] -= this->regx[regA];
                if (!this->regx[regB]) this->regx[5] |= 1;
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
                
                break;
            case isa::LDM:
                if (this->modes[3]) {
                    this->regx[regB] = this->hiddenReg[2];
                    this->modes[3] = 0;
                    this->modes[2] = 0;
                } else {
                    this->hiddenReg[2] = this->regx[regA];
                    this->modes[2] = 2;
                    stage = 4;
                    return;
                }
                break;
            case isa::STR:
                this->Send(8 , 1);
                this->Send(9 , this->regx[regA]);
                this->Send(10 , this->regx[regB]);
                break;
            case isa::LDR:
                this->regx[regB] = this->regx[regA];
                break;
            case isa::JMP: {
                int mode = opmode;
                if (mode) {
                    this->regx[7] += (signed char)(instr & 0xff);
                } else {
                    this->regx[7] = this->regx[regA];
                }
                goto end;
            }
            case isa::JZE: {
                int mode = opmode;
                if (mode) {
                    if (this->regx[5] & 1) this->regx[7] += (signed char)(instr & 0xff);
                    else break;
                    goto end;
                } else {
                    if (this->regx[5] & 1) this->regx[7] = this->regx[regA];
                    else break;
                    goto end;
                }
                break;
            }
            case isa::JEQ: {
                int mode = opmode;
                if (mode) {
                    if (this->regx[5] & 2) this->regx[7] += (signed char)(instr & 0xff);
                    else break;
                    goto end;
                } else {
                    if (this->regx[5] & 2) this->regx[7] = this->regx[regA];
                    else break;
                    goto end;
                }
            }
            case isa::JNE: {
                int mode = opmode;
                if (mode) {
                    if (! (this->regx[5] & 2)) this->regx[7] += (signed char)(instr & 0xff);
                    else break;
                    goto end;
                } else {
                    if (!(this->regx[5] & 2)) this->regx[7] = this->regx[regA];
                    else break;
                    goto end;
                }
            }
            case isa::JLT: {
                if (this->regx[5] & 2) break;
                int mode = opmode;
                if (mode) {
                    if (this->regx[5] & 4) this->regx[7] += (signed char)(instr & 0xff);
                    else break;
                    goto end;
                } else {
                    if (this->regx[5] & 4) this->regx[7] = this->regx[regA];
                    else break;
                    goto end;
                }
            }
            case isa::JGT: {
                if (this->regx[5] & 2) break;
                int mode = opmode;
                if (mode) {
                    if (!(this->regx[5] & 4)) this->regx[7] += (signed char)(instr & 0xff);
                    else break;
                    goto end;
                } else {
                    if (!(this->regx[5] & 4)) this->regx[7] = this->regx[regA];
                    else break;
                    goto end;
                }
            }
            case isa::CMP: {
                auto& reg1 = this->regx[regA];
                auto& reg2 = this->regx[regB];
                auto& flag = this->regx[5];
                flag = 0;
                if (reg1 == reg2) flag |= 2;
                if (reg1 < reg2) flag |= 4;
                break;
            }
            default: {
                break;
            }
            }
        }
        this->regx[7]++;
        end:
        stage = 1;
        return;
    } else if (stage == 4) {
        // request data;
        auto addr = this->hiddenReg[2];
        //auto dest = this->hiddenReg[3];
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

