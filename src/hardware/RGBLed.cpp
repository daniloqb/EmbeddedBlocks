#include <EmbeddedBlocks/hardware/RGBLed.h>
#include <Arduino.h>

namespace eb
{

    RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin):
        m_red(redPin),
        m_green(greenPin),
        m_blue(bluePin),
        m_Rvalue(0),
        m_Gvalue(0),
        m_Bvalue(0),
        m_brightness(100),
        m_state(false)
    {
       
    }

    void RGBLed::begin()
    {
        m_red.begin();
        m_green.begin();
        m_blue.begin();
    }
    void RGBLed::setColor(uint32_t red, uint32_t green, uint32_t blue)
    {
        m_Rvalue = red;
        m_Gvalue = green;
        m_Bvalue = blue;

        if (m_state)
        {
            m_red.write((m_Rvalue * m_brightness) / 100);
            m_green.write((m_Gvalue * m_brightness) / 100);
            m_blue.write((m_Bvalue * m_brightness) / 100);
        }
    }
    void RGBLed::on()
    {
        m_state = true;
        m_red.write((m_Rvalue * m_brightness) / 100);
        m_green.write((m_Gvalue * m_brightness) / 100);
        m_blue.write((m_Bvalue * m_brightness) / 100);
    }
    void RGBLed::off()
    {
        m_state = false;
        m_red.write(0);
        m_green.write(0);
        m_blue.write(0);
    }

    void RGBLed::setBrightness(uint8_t brightness)
    {
        m_brightness = constrain(brightness, 0, 100);
        if (m_state)
        {
            m_red.write((m_Rvalue * m_brightness) / 100);
            m_green.write((m_Gvalue * m_brightness) / 100);
            m_blue.write((m_Bvalue * m_brightness) / 100);
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