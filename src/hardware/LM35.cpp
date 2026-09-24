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
        float millivolts = m_analogInput.getMillivolts();
       
        setTemperature(millivolts / 10.0); // LM35 gives 10mV per degree Celsius
    }
    float LM35::getMillivolts() const
    {
        return m_analogInput.getMillivolts();
    }




} // namespace eb