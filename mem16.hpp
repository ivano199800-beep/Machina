#pragma once
#include <array>
#include "devices.hpp"



namespace machina {
    class mem16 : public device {
        std::array<uint16_t , 0x10000> data;
        public:
            void tick() override;
    };
}