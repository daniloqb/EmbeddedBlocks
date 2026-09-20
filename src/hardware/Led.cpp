#include <EmbeddedBlocks/hardware/Led.h>
#include <Arduino.h>

namespace eb
{
    Led::Led(uint8_t pin) : m_pin(pin),
                        m_state(false)
    {
    }

    void Led::begin()

    {

      // Initialize the LED pin as an output
        pinMode(m_pin, OUTPUT);
        off();
    }

    // void Led::update()
    // {
    // }

    void Led::on()
    {
        digitalWrite(m_pin, HIGH);
        m_state = true;
    }

    void Led::off()
    {
        digitalWrite(m_pin, LOW);
        m_state = false;
    }

    void Led::toggle()
    {
        if (m_state)
        {
            off();
        }
        else
        {
            on();
        }
    }

}
