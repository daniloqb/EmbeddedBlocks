#include <EmbeddedBlocks/hardware/Button.h>
#include <Arduino.h>

namespace eb
{
    Button::Button(uint8_t pin, ButtonConfig config)
        : m_pin(pin), m_config(config), m_lastReading(false), m_state(ButtonState::UP),
          m_lastStateChange(0), m_heldStart(0), m_event(ButtonEvent::NONE), m_clickCount(0), m_lastClickTime(0), m_eventClick(ButtonEvent::NONE)
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
        if (m_state == ButtonState::HELD && m_lastReading) // if the button is held and still being pressed, do nothing
            return;

        // Update the button state if it has changed
        if (m_state != (m_lastReading ? ButtonState::DOWN : ButtonState::UP))
        {
            m_state = m_lastReading ? ButtonState::DOWN : ButtonState::UP;                           // update the button state based on the last stable reading
            m_event = (m_state == ButtonState::DOWN) ? ButtonEvent::PRESSED : ButtonEvent::RELEASED; // set the event based on the new state

            // If the button is now down, record the time it was pressed. Start the held timer.
            if (m_state == ButtonState::DOWN)
            {
                m_heldStart = millis();
                m_lastClickTime = millis(); // record the time of the last click
                m_clickCount++;             // increment the click count
            }
            else
            {
                // Check for click and double click events
                if (m_state == ButtonState::UP)
                {
                    uint32_t now = millis();
           
                    if (now - m_lastClickTime <= m_clickThreshold)
                    {
                        if (m_clickCount == 1)
                        {
                            m_eventClick = eb::ButtonEvent::CLICK; // Set the click event
                            
                        }
                        else if (m_clickCount == 2)
                        {
                            m_eventClick = eb::ButtonEvent::DOUBLE_CLICK; // Set the double click event
                            m_clickCount = 0;                     // Reset click count after double click
                        }
                    }else
                    {
                        m_clickCount = 0; // Reset click count if the click threshold has passed
                        m_eventClick = eb::ButtonEvent::LONG_CLICK; // Reset the click event if the click threshold has passed
                    }
          
                }
            }
        }
        else
        {
            // Check if the button has been held long enough to trigger a held event
            if (m_state == ButtonState::DOWN && (millis() - m_heldStart >= m_heldThreshold))
            {
                m_event = eb::ButtonEvent::HELD_START;
                m_state = ButtonState::HELD;
            }
        }
        // Reset click count if the click threshold has passed
        if ( millis() - m_lastClickTime > m_clickThreshold)
        {
            m_clickCount = 0;
        }
    }

    eb::ButtonEvent Button::getEvent()
    {
        eb::ButtonEvent event = m_event;
        m_event = eb::ButtonEvent::NONE; // Reset the event after reading it
        return event;
    }

    eb::ButtonEvent Button::getEventClick()
    {
        eb::ButtonEvent event = m_eventClick;
        m_eventClick = eb::ButtonEvent::NONE; // Reset the click event after reading it
        return event;
    }

}