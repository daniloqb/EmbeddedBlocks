#pragma once
#include <stdint.h>

namespace eb
{

    enum class ButtonConfig
    {
        PULLUP,
        PULLDOWN
    };

    enum class ButtonEvent
    {
        NONE,
        PRESSED,
        RELEASED,
        HELD_START,
    };

    enum class ButtonState
    {
        UP,
        DOWN,
        HELD,
    };

    class Button
    {
    public:
        Button(uint8_t pin, ButtonConfig config = ButtonConfig::PULLUP);
        void begin();
        void update();
        ButtonState getState() const { return m_state; }
        ButtonEvent getEvent();
        bool isPressed() const { return m_state == ButtonState::DOWN || m_state == ButtonState::HELD; }

    private:
        uint8_t m_pin;
        ButtonConfig m_config;
        ButtonState m_state = ButtonState::UP;
        bool m_lastReading = false;
        uint32_t m_lastStateChange = 0;
        uint32_t m_heldStart = 0;
        static const uint32_t m_heldThreshold = 1000;   // Time in milliseconds to consider the button held
        static const uint32_t m_debounceThreshold = 50; // Time in milliseconds for debounce
        ButtonEvent m_event = ButtonEvent::NONE;
    };
}