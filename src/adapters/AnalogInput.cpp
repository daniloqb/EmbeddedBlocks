#include <EmbeddedBlocks/adapters/AnalogInput.h>
#include <Arduino.h>

namespace eb
{

    AnalogInput::AnalogInput(uint8_t pin)
    {
        m_pin = pin;
    }

    void AnalogInput::begin()
    {
        pinMode(m_pin, INPUT);
    }

    void AnalogInput::update()
    {
        // Read the ADC value from the analog input pin
        m_ADCValue = analogRead(m_pin);
    }

    float AnalogInput::getVoltageReference() const
    {
        return m_voltageReference;
    }

    void AnalogInput::setVoltageReference(float voltageReference)
    {
        m_voltageReference = voltageReference;
    }

    uint32_t AnalogInput::getADCResolution() const
    {
        return m_ADCResolution;
    }

    void AnalogInput::setADCResolution(uint32_t adcResolution)
    {
        m_ADCResolution = adcResolution;
    }
    uint32_t AnalogInput::getADCValue() const
    {
        return m_ADCValue;
    }

} // namespace eb