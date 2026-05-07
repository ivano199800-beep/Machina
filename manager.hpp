
    #include "devices.hpp"
    
    namespace machina {
        class manager : public device {
            void tick() override;
            void start() override;
        };            
    }
    