#include <EmbeddedBlocks/hardware/PWMLed.h>
#include <Arduino.h>

namespace eb
{

    eb::PWMLed::PWMLed(uint8_t pin)
    {
        m_pin = pin;
        m_state = false;
        m_brightness = 100;
    }
    void PWMLed::begin()
    {
        pinMode(m_pin, OUTPUT);
        off();
    }
    void PWMLed::setBrightness(uint8_t brightness)
    {

        if (brightness > 100)
        {
            brightness = 100;
        }
        else
        {
            m_brightness = brightness; // brightness is within range, do nothing
        }

        if (m_state)
        {
            uint32_t pwmValue = (m_brightness * PWM_MAX()) / 100;
            analogWrite(m_pin, pwmValue);
        }
    }
    void PWMLed::on()
    {
        m_state = true;
        setBrightness(m_brightness);
    }

    void PWMLed::off()
    {
        m_state = false;
        analogWrite(m_pin, 0);
    }

    void PWMLed::toggle()
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