#include <EmbeddedBlocks/hardware/Button.h>
#include <Arduino.h>

namespace eb
{
    Button::Button(uint8_t pin, ButtonConfig config)
        : m_pin(pin), m_isPressed(false), m_config(config)
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
        if (m_config == ButtonConfig::PULLUP)
        {
            m_isPressed = digitalRead(m_pin) == LOW;
        }
        else
        {
            m_isPressed = digitalRead(m_pin) == HIGH;
        }
    }

    bool Button::isPressed()
    {
        return m_isPressed;
    }

}