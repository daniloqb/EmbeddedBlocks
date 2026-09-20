#pragma once
#include <stdint.h>

namespace eb{
    class PWM
    {
    public:
        explicit PWM(uint8_t pin, uint32_t maxPWM = 255);
        void begin();
        void write(uint8_t value);
        
    private:
        uint8_t m_pin;
        uint32_t m_maxPWM;
    };
}