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
        uint32_t getADCMaxValue() const;
        void setADCMaxValue(uint32_t adcMaxValue);
        uint32_t getADCValue() const;
        uint16_t getSamplesPerUpdate() const;
        void setSamplesPerUpdate(uint16_t samplesPerUpdate);
        float getMillivolts() const;

    private:
        uint8_t m_pin;
        uint16_t m_samplesPerUpdate = 1;
        uint32_t m_ADCValue = 0;
        float m_voltageReference = 5.0f;
        uint32_t m_ADCMaxValue = 1023;
    };
} // namespace eb