#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::PWMLed led(3);

void setup()
{
    led.begin();
    led.setBrightness(1);
}

void loop()
{
    led.toggle();
    delay(500); // Add a delay to make the LED toggle visible
}