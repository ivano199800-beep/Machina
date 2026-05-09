#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <map>
#include <cstring>
typedef uint16_t WORD_;
typedef uint8_t HWORD_;
namespace machina {
    typedef struct {
        uint16_t data;
    } BusLine;
    typedef struct {
        BusLine* line;
    } Port;
    class device {
        std::vector<Port> ports;
        char did[17];
        WORD_ dType;
        size_t Deviceflag , port_count , port_available;
        
        public:
        device() {
            Deviceflag = 0;
            port_count = 0;
            port_available = 0;
            dType = 0;
            for (int i = 0 ; i < 16 ; i++) {
                did[i] = 0;
            }
        }
        void RegisterDID(const std::string& name) {
            if (this->Deviceflag & 2) return; 
            const char* s = name.c_str();
            strncpy(this->did , s, 16);
            this->did[16] = 0;
            this->Deviceflag |= 2;
        }
        void RegisterPortS1(size_t port_count) {
            if (Deviceflag & 1) return;
            this->port_available = port_count;
            this->port_count = port_count;
            Deviceflag |= 1;
        }
        void RegisterPortS2(Port port) {
            if (!port_available) return; 
            ports.push_back(port);
            port_available--;
        }
        // void RegisterType(uint16_t dType) {
        //     int s = machina::Device::deviceMap[dType];
        // }
        void Send(size_t port_num , WORD_ data) {
            if (port_num >= port_count) return;
            this->ports[port_num].line->data = data;
            std::cout << this->did << ": 0x" << std::hex << (int)data << " >  P0x" << std::hex << port_num << std::endl;
        }
        uint16_t Receive(size_t port_num) {
            if (port_num >= port_count) return 0;
            int data = this->ports[port_num].line->data;
            std::cout << this->did << ": 0x" << std::hex << (int)data << " < P0x" <<  std::hex << port_num << std::endl;
            return data;
        }
        // void SetID(const std::string& s) {
        //     for (size_t i = 0 ; i < 16 && i < s.length() ; i++) {
        //         this->did[i]  = s[i];
        //     }
        //     this->did[16] = 0;
        // }
        // static void RegisterType(std::string& device);
        virtual void tick() {
            std::cout << "WIP" << '\n';
        }
        virtual void start() {
            std::cout << "WIP" << '\n';
        };
        private:
    };
}

// useless comment