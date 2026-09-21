#pragma once
#include <stdint.h>
#include <EmbeddedBlocks/core/PWM.h>

namespace eb
{
    class LedRGB
    {
    public:
        explicit LedRGB(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
        void begin();
        void on();
        void off();
        void toggle();

        void setHue(uint16_t hue);
        void setColor(uint8_t red, uint8_t green, uint8_t blue);
        void setBrightness(uint8_t brightness);
        void setSaturation(uint8_t saturation);
        void randomHue();
        uint8_t getBrightness();

        static constexpr uint32_t PWM_MAX = 255;

    private:
        PWM m_red;
        PWM m_green;
        PWM m_blue;
        uint8_t m_Rvalue;
        uint8_t m_Gvalue;
        uint8_t m_Bvalue;
        uint8_t m_brightness;
        uint8_t m_saturation;
        uint16_t m_hue;
        bool m_state;

    private:
        void applyColor();
        void updateColorFromHSV();
        uint16_t rgbToHue(uint8_t red, uint8_t green, uint8_t blue);
    };
}