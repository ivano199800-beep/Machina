#include "devices.hpp"
#include <array>

namespace machina {
    using INSTR_ = WORD_;
    class core16 : public device {
        WORD_ regx[8];
        enum class isa : HWORD_ {
            NOP = 0,
            HLT,
            JMP,
            JZE,
            JOF,
            JNE,
            JCA,
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
            SFT,
            RCV,
            SND
        };
        // ra rb rc rd re rf sp ip or 
        // accumilator base count data extra flag stack_pointer instruction_pointer
        std::array<INSTR_ , 32> instruction_cache;
        std::array<WORD_ , 16> hiddenReg; 
        std::array<HWORD_ , 16> modes = {0};
        WORD_ stage = 0;
        const char size_of_instr = sizeof(WORD_) * 8;
        //instruction packing
        //[opcode][mode][regA][regB] if (op == ldi) + [IMM16]
        public:
        void tick() override;
        void start() override;
        void set(WORD_ key , HWORD_ value);
    };
}