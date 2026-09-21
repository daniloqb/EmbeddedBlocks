#include <EmbeddedBlocks/hardware/LedPWM.h>
#include <Arduino.h>

namespace eb
{

    LedPWM::LedPWM(uint8_t pin):
        m_pwm(pin),
        m_state(false),
        m_brightness(100)
        
    {

    }
    void LedPWM::begin()
    {
        m_pwm.begin();
        off();
    }
    void LedPWM::setBrightness(uint8_t brightness)
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
    void LedPWM::on()
    {
        m_state = true;
        setBrightness(m_brightness);
    }

    void LedPWM::off()
    {
        m_state = false;
        m_pwm.write(0);
    }

    void LedPWM::toggle()
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