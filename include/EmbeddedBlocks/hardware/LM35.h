#pragma once
#include <EmbeddedBlocks/hardware/TemperatureSensor.h>
#include <EmbeddedBlocks/adapters/AnalogInput.h>

namespace eb
{
    class LM35 : public TemperatureSensor
    {
    public:
        explicit LM35(AnalogInput& analogInput);
        void begin() override;
        void update() override;
        float getMillivolts() const;


    private:
        AnalogInput& m_analogInput;
    };

} // namespace eb