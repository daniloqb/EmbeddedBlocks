#include <Arduino.h>
#include <EmbeddedBlocks/hardware/LM35.h>

namespace eb
{
    LM35::LM35(AnalogInput& analogInput) : m_analogInput(analogInput) {}

    void LM35::begin()
    {
        m_analogInput.begin();
    }

    void LM35::update()
    {
        m_analogInput.update();
        int sensorValue = m_analogInput.getADCValue();
        m_milivolts = sensorValue * (m_analogInput.getVoltageReference() * 1000 / m_analogInput.getADCResolution()); // Convert to millivolts
        m_temperature = m_milivolts / 10.0; // LM35 gives 10mV per degree Celsius
    }


    uint32_t LM35::getMillivolts() const
    {
        return m_milivolts;
    }

} // namespace eb