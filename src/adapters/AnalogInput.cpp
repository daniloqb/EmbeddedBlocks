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
        m_ADCValue = 0;
        for (uint16_t i = 0; i < m_samplesPerUpdate; ++i)
        {
            m_ADCValue += analogRead(m_pin);
        }
        m_ADCValue /= m_samplesPerUpdate;
    }

    float AnalogInput::getVoltageReference() const
    {
        return m_voltageReference;
    }

    void AnalogInput::setVoltageReference(float voltageReference)
    {
        m_voltageReference = voltageReference;
    }

    uint32_t AnalogInput::getADCMaxValue() const
    {
        return m_ADCMaxValue;
    }

    void AnalogInput::setADCMaxValue(uint32_t adcMaxValue)
    {
        m_ADCMaxValue = adcMaxValue;
    }
    uint32_t AnalogInput::getADCValue() const
    {
        return m_ADCValue;
    }

    uint16_t AnalogInput::getSamplesPerUpdate() const
    {
        return m_samplesPerUpdate;
    }

    void AnalogInput::setSamplesPerUpdate(uint16_t samplesPerUpdate)
    {
        m_samplesPerUpdate = samplesPerUpdate;  
    }
    float AnalogInput::getMillivolts() const
    {
        return m_ADCValue * (m_voltageReference * 1000 / m_ADCMaxValue);
    }

} // namespace eb