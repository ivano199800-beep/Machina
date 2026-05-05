#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
namespace machina {
    typedef struct {
        uint16_t data;
    } BusLine;
    typedef struct {
        BusLine* line;
    } Port;
    class Device {
        std::vector<Port> ports;
        char did[17];
        size_t Deviceflag , port_count , port_available;
        public:
        Device() {
            Deviceflag = 0;
            port_count = 0;
            port_available = 0;
            for (int i = 0 ; i < 16 ; i++) {
                did[i] = 0;
            }
        }
        void RegisterPortS1(size_t port_count) {
            if (Deviceflag & 1) return;
            this->port_available = port_count;
            this->port_count = port_count;
            Deviceflag |= 1;
        }
        void RegisterPortS2(Port port) {
            if (port_available) ports.push_back(port);
            else { port_available = 0; return; } 
            port_available--;
        }
        void Send(size_t port_num , uint16_t data) {
            if (port_num >= port_count) return;
            this->ports[port_num].line->data = data;
        }
        uint16_t Receive(size_t port_num) {
            if (port_num >= port_count) return 0;
            return this->ports[port_num].line->data;
        }
        void SetID(const std::string& s) {
            for (int i = 0 ; i < 16 && i < s.length() ; i++) {
                this->did[i]  = s[i];
            }
            this->did[16] = 0;
        }
        virtual void tick() {
            std::cout << "WIP" << '\n';
        }
    };
}