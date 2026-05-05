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
            SFT
        };
        // ra rb rc rd re rf sp ip or 
        // accumilator base count data extra flag stack_pointer instruction_pointer
        size_t state = 0; // idle fetch execute pend
        // pack the instruction into one WORD_ with the first nibble and bit the opcode and
        // the rest of the byte is the mode then the 2 byte is the regIdx or another mode
        // the only immediate loading is ldi STR LDM JMP and etc all use a register to operate
        void tick() override;
    };
}