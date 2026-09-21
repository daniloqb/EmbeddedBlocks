#pragma once
#include <stdint.h>
#include <EmbeddedBlocks/core/PWM.h>

namespace eb
{
    class LedPWM
    {
    public:
        explicit LedPWM(uint8_t pin);
        void begin();
        // void update();

        void toggle();
        void on();
        void off();
        void setBrightness(uint8_t brightness);
        uint8_t getBrightness() const { return m_brightness; }

    private:
        PWM m_pwm;
        bool m_state;
        uint8_t m_brightness;
    };
}