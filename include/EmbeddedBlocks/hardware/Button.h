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
        CLICK,
        DOUBLE_CLICK,
        LONG_CLICK,
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
        ButtonEvent getGestureEvent();

    private:
        uint8_t m_pin;
        ButtonConfig m_config;
        bool m_lastReading = false;
        uint32_t m_lastStateChange = 0;
        uint32_t m_heldStart = 0;
        
        ButtonState m_state = ButtonState::UP;
        ButtonState m_previousState = ButtonState::UP;
        ButtonEvent m_gestureEvent = ButtonEvent::NONE;
        ButtonEvent m_event = ButtonEvent::NONE;

        static const uint32_t m_clickThreshold = 250; // Time in milliseconds to consider a click
        static const uint32_t m_doubleClickThreshold = 250; // Time in milliseconds to consider a double click
        static const uint32_t m_heldThreshold = 1000;   // Time in milliseconds to consider the button held
        static const uint32_t m_debounceThreshold = 30; // Time in milliseconds for debounce

    private:
        bool m_clickPending = false;
        bool m_secondClickCandidate = false;
        uint32_t m_firstClickReleaseTime = 0; // Time of the last click
    };
}