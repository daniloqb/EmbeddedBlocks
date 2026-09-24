#pragma once
#include <stdint.h>

namespace eb
{
    class AnalogInput
    {
    public:
        AnalogInput(uint8_t pin);

        void begin();
        void update();

        float getVoltageReference() const;
        void setVoltageReference(float voltageReference);
        uint32_t getADCResolution() const;
        void setADCResolution(uint32_t adcResolution);
        uint32_t getADCValue() const;
    
    private:

        uint8_t m_pin;
        uint32_t m_ADCValue = 0;
        float m_voltageReference = 5.0f;
        uint32_t m_ADCResolution = 1023;
    };
} // namespace eb