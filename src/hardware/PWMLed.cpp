#include <EmbeddedBlocks/hardware/PWMLed.h>
#include <Arduino.h>

namespace eb
{

    eb::PWMLed::PWMLed(uint8_t pin):
        m_pwm(pin),
        m_state(false),
        m_brightness(100)
        
    {

    }
    void PWMLed::begin()
    {
        m_pwm.begin();
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
            uint32_t pwmValue = (m_brightness * 255) / 100;
            m_pwm.write(pwmValue);
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
        m_pwm.write(0);
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