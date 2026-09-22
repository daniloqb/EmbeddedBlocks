#include <EmbeddedBlocks/hardware/Button.h>
#include <Arduino.h>

namespace eb
{
    Button::Button(uint8_t pin, ButtonConfig config)
        : m_pin(pin), m_config(config), m_lastReading(false), 
          m_lastStateChange(0), m_heldStart(0), m_state(ButtonState::UP), m_gestureEvent(ButtonEvent::NONE), m_event(ButtonEvent::NONE)
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

        // m_state = m_lastState ? ButtonState::DOWN : ButtonState::UP;
        if (m_state == ButtonState::HELD && m_lastReading) // if the button is held and still being pressed, do nothing
            return;

        // Update the button state if it has changed
        if (m_state != (m_lastReading ? ButtonState::DOWN : ButtonState::UP))
        {
            m_previousState = m_state;
            m_state = m_lastReading ? ButtonState::DOWN : ButtonState::UP;                           // update the button state based on the last stable reading
            m_event = (m_state == ButtonState::DOWN) ? ButtonEvent::PRESSED : ButtonEvent::RELEASED; // set the event based on the new state

            // If the button is now down, record the time it was pressed. Start the held timer.
            if (m_state == ButtonState::DOWN)
            {
                uint32_t currentTime = millis();
                m_heldStart = currentTime;

                if (m_clickPending)
                {
                    if (currentTime - m_firstClickReleaseTime <= m_doubleClickThreshold)
                    {
                        m_secondClickCandidate = true;
                    }
                    else
                    {
                        m_gestureEvent = eb::ButtonEvent::CLICK;
                        m_clickPending = false;
                    }
                }
            }
            else
            {
                // Check for click and double click events
                if (m_state == ButtonState::UP)
                {
                    if (m_previousState == ButtonState::DOWN)
                    {

                        if (m_secondClickCandidate)
                        {
                            m_gestureEvent = eb::ButtonEvent::DOUBLE_CLICK;
                            m_clickPending = false;
                            m_secondClickCandidate = false;
                        }
                        else
                        {
                            m_clickPending = true;
                            m_firstClickReleaseTime = millis();
                        }
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
                m_previousState = m_state;
                m_state = ButtonState::HELD;

                m_clickPending = false;
                m_gestureEvent = eb::ButtonEvent::LONG_CLICK;
                m_firstClickReleaseTime = 0;
                m_secondClickCandidate = false;
            }
        }

        if (m_clickPending && (millis() - m_firstClickReleaseTime > m_doubleClickThreshold))    
        {
            m_gestureEvent = eb::ButtonEvent::CLICK;
            m_clickPending = false;
        }
    }

    eb::ButtonEvent Button::getEvent()
    {
        eb::ButtonEvent event = m_event;
        m_event = eb::ButtonEvent::NONE; // Reset the event after reading it
        return event;
    }

    eb::ButtonEvent Button::getGestureEvent()
    {
        eb::ButtonEvent event = m_gestureEvent;
        m_gestureEvent = eb::ButtonEvent::NONE; // Reset the click event after reading it
        return event;
    }

}