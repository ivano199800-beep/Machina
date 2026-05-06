#include "devices.hpp"


namespace machina {
    class core : public device {
        WORD_ regx[8];
        enum class isa : uint8_t {
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
        size_t state = 0; // idle fetch execute pend
        const char size_of_instr = sizeof(WORD_) * 8;
        //instruction packing
        //[opcode][mode][regA][regB] if (op == ldi) + [IMM16]
        void tick() override;
    };
}