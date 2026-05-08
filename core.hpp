#include "devices.hpp"
#include <array>

namespace machina {
    using INSTR_ = WORD_;
    class core16 : public device {
        WORD_ regx[8];
        public:
        enum class isa : HWORD_ {
            NOP = 0,
            HLT,
            JMP,
            JZE,
            JEQ,
            JNE,
            JLT,
            JGT,
            LDI,
            LDM,
            LDR,
            STR,
            PSH,    
            POP,
            CAL,
            RET,
            ADD,
            SUB,
            CMP,
            SFT,
            RCV,
            SND
        };
        private:
        // ra rb rc rd re rf sp ip or 
        // accumilator base count data extra flag stack_pointer instruction_pointer
        std::array<INSTR_ , 32> instruction_cache;
        std::array<WORD_ , 16> hiddenReg; 
        std::array<HWORD_ , 32> modes = {0};
        WORD_ stage = 0;
        const char sizeof_instr = sizeof(WORD_) * 8;
        //instruction packing
        //[opcode][mode][regA][regB] if (op == ldi) + [IMM16]
        public:
        void tick() override;
        void start() override;
        void set(HWORD_ key , HWORD_ value);
        INSTR_ assemble(HWORD_ opcode, HWORD_ opmode, HWORD_ B, HWORD_ A, HWORD_ rMode) {
        return ((opcode & 0x1F) << 11) | 
           ((opmode & 0x07) << 8)  | 
           ((B      & 0x07) << 5)  | 
           ((A      & 0x07) << 2)  | 
           (rMode   & 0x03);
    }
    };


}