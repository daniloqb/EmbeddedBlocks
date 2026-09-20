#include <EmbeddedBlocks/hardware/RGBLed.h>
#include <Arduino.h>

namespace eb
{

    RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
    {
        m_redPin = redPin;
        m_greenPin = greenPin;
        m_bluePin = bluePin;
        m_Rvalue = 0;
        m_Gvalue = 0;
        m_Bvalue = 0;
        m_brightness = 100;
        m_state = false;
    }

    void RGBLed::begin()
    {
        // Initialize the RGB LED pins as output
        pinMode(m_redPin, OUTPUT);
        pinMode(m_greenPin, OUTPUT);
        pinMode(m_bluePin, OUTPUT);
    }
    void RGBLed::setColor(uint32_t red, uint32_t green, uint32_t blue)
    {
        m_Rvalue = red;
        m_Gvalue = green;
        m_Bvalue = blue;

        if (m_state)
        {
            analogWrite(m_redPin, (m_Rvalue * m_brightness) / 100);
            analogWrite(m_greenPin, (m_Gvalue * m_brightness) / 100);
            analogWrite(m_bluePin, (m_Bvalue * m_brightness) / 100);
        }
    }
    void RGBLed::on()
    {
        m_state = true;
        analogWrite(m_redPin, (m_Rvalue * m_brightness) / 100);
        analogWrite(m_greenPin, (m_Gvalue * m_brightness) / 100);
        analogWrite(m_bluePin, (m_Bvalue * m_brightness) / 100);
    }
    void RGBLed::off()
    {
        m_state = false;
        analogWrite(m_redPin, 0);
        analogWrite(m_greenPin, 0);
        analogWrite(m_bluePin, 0);
    }

    void RGBLed::setBrightness(uint8_t brightness)
    {
        m_brightness = brightness;
        if (m_state)
        {
            analogWrite(m_redPin, (m_Rvalue * m_brightness) / 100);
            analogWrite(m_greenPin, (m_Gvalue * m_brightness) / 100);
            analogWrite(m_bluePin, (m_Bvalue * m_brightness) / 100);
        }
    }

    uint8_t RGBLed::getBrightness()
    {
        return m_brightness;
    }   

    void RGBLed::toggle()
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