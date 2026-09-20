#pragma once
#include <stdint.h>

namespace eb
{
    class Led
    {
    public:
        explicit Led(uint8_t pin);
        void begin();
        //void update();

        void toggle();
        void on();
        void off();

    private:
        uint8_t m_pin;
        bool m_state;
    };
}