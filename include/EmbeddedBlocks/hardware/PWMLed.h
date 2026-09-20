#pragma once
#include <stdint.h>

namespace eb
{
    class PWMLed
    {
    public:
        explicit PWMLed(uint8_t pin);
        void begin();
        // void update();

        void toggle();
        void on();
        void off();
        void setBrightness(uint8_t brightness);
        uint8_t getBrightness() const { return m_brightness; }
        static constexpr uint32_t PWM_MAX() { return 255; }

    private:
        uint8_t m_pin;
        bool m_state;
        uint8_t m_brightness;
    };
}