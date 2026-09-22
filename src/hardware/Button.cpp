#include <EmbeddedBlocks/hardware/Button.h>
#include <Arduino.h>

namespace eb
{
    Button::Button(uint8_t pin, ButtonConfig config)
        : m_pin(pin), m_config(config), m_lastReading(false), m_state(ButtonState::UP),
          m_lastStateChange(0), m_heldStart(0), m_event(ButtonEvent::NONE)
    {
    }

    void Button::begin()
    {
        if (m_config == ButtonConfig::PULLUP)
        {
            pinMode(m_pin, INPUT_PULLUP);
        }
        else
        {
            pinMode(m_pin, INPUT);
        }
    }

    void Button::update()
    {

        // read digital input from the button pin
        // adjust for pull-up configuration
        bool read = digitalRead(m_pin);
        read = (m_config == ButtonConfig::PULLUP) ? !read : read;

        // Check if the button state has changed
        // if the state has changed, update the last state and the last state change time
        if (read != m_lastReading)
        {
            m_lastReading = read;
            m_lastStateChange = millis();
        }
        // Debounce check
        // If the button state has not changed for longer than the debounce threshold, update the state
        //
        if (millis() - m_lastStateChange < m_debounceThreshold)
        {
            return;
        }

        // Update the button state based on the last stable reading
        // m_state = m_lastState ? ButtonState::DOWN : ButtonState::UP;
        if (m_state == ButtonState::HELD && m_lastReading)
            return;

        if (m_state != (m_lastReading ? ButtonState::DOWN : ButtonState::UP))
        {
            m_state = m_lastReading ? ButtonState::DOWN : ButtonState::UP;
            m_event = (m_state == ButtonState::DOWN) ? ButtonEvent::PRESSED : ButtonEvent::RELEASED;
            if (m_state == ButtonState::DOWN)
                m_heldStart = millis();
        }
        else
        {

            if (m_state == ButtonState::DOWN && (millis() - m_heldStart >= m_heldThreshold))
            {
                m_event = eb::ButtonEvent::HELD_START;
                m_state = ButtonState::HELD;
            }
        }
    }

    eb::ButtonEvent Button::getEvent()
    {
        eb::ButtonEvent event = m_event;
        m_event = eb::ButtonEvent::NONE; // Reset the event after reading it
        return event;
    }

}