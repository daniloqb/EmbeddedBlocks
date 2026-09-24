#pragma once
#include <EmbeddedBlocks/hardware/TemperatureSensor.h>
#include <EmbeddedBlocks/adapters/AnalogInput.h>

namespace eb
{
    class LM35 : public TemperatureSensor
    {
    public:
        LM35(AnalogInput& analogInput);
        void begin() override;
        void update() override;
        uint32_t getMillivolts() const;

    private:
        AnalogInput m_analogInput;
        uint32_t m_milivolts = 0;
    };

} // namespace eb