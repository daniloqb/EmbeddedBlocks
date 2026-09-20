#pragma once
#include <stdint.h>
#include <EmbeddedBlocks/core/PWM.h>

namespace eb
{
    class RGBLed
    {
    public:
        explicit RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
        void begin();
        void on();
        void off();
        void toggle();

        void setColor(uint32_t red, uint32_t green, uint32_t blue);
        void setBrightness(uint8_t brightness);
        uint8_t getBrightness();

        static constexpr uint32_t PWM_MAX = 255;

    private:
        PWM m_red;
        PWM m_green;
        PWM m_blue;
        uint32_t m_Rvalue;
        uint32_t m_Gvalue;
        uint32_t m_Bvalue;
        uint8_t m_brightness;
        bool m_state;
    };
}