#pragma once
#include <array>
#include "devices.hpp"



namespace machina {
    class mem16 : public device {
        std::array<uint16_t , 0x10000> data = {1};
        size_t lane = 0; // not implemented
            public:
            void tick() override;
            void start() override;
    };
}