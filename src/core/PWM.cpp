#include <EmbeddedBlocks/core/PWM.h>
#include <Arduino.h>

namespace eb
{

    PWM::PWM(uint8_t pin, uint32_t maxPWM)
        : m_pin(pin), m_maxPWM(maxPWM)
    {
    }
    void PWM::begin()
    {
        // Initialize the PWM pin here if necessary
    }
    void PWM::write(uint8_t value)
    {
        uint32_t pwmValue = (static_cast<uint32_t>(value) * m_maxPWM) / 255;
        analogWrite(m_pin, pwmValue);
    }
}
