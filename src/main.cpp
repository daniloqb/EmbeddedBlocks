#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::AnalogInput analogInput(A0);
eb::LM35 lm35(analogInput);

void setup()
{
    analogInput.setSamplesPerUpdate(10);
    lm35.begin();
    Serial.begin(9600);
}

void loop()
{
    lm35.update();
    float temperatureC = lm35.getTemperatureCelsius();
    Serial.print(temperatureC);
    Serial.print("(C): ");

    Serial.print(lm35.getMillivolts());
    Serial.println("mV");
    delay(1000);
}