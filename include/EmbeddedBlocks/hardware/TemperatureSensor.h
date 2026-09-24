#pragma once
#include <stdint.h>

namespace eb
{
    class TemperatureSensor
    {
    public:
        virtual ~TemperatureSensor() = default;
        virtual void begin() = 0;
        virtual void update() = 0;

        float getTemperatureCelsius() const { return m_temperature; };
        float getTemperatureFahrenheit() const { return m_temperature * 9.0 / 5.0 + 32; };
        float getTemperatureKelvin() const { return m_temperature + 273.15; };
        float getCalibratedTemperature() const { return (m_temperature * m_calibrationGain) + m_calibrationOffset; };
        bool isValid() const { return valid; };
         uint32_t getLastUpdateTimestamp() const { return m_lastUpdateTimestamp; };

    protected:
        float m_temperature = 0.0f;
        float m_calibrationOffset = 0.0f;
        float m_calibrationGain = 1.0f;
        bool valid = false;
        uint32_t m_lastUpdateTimestamp = 0; 
       
    };

} // namespace eb