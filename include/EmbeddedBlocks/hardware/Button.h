#pragma once
#include <stdint.h>

namespace eb
{

    enum class ButtonConfig
    {
        PULLUP,
        PULLDOWN
    };

    class Button
    {
    public:
        Button(uint8_t pin, ButtonConfig config=ButtonConfig::PULLUP);
        void begin();
        void update();
        bool isPressed();

    private:
        uint8_t m_pin;
        bool m_isPressed;
        ButtonConfig m_config;
    };
}