#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::Led led(9);


void setup()
{
    led.begin();
    led.off();
}

void loop()
{
    led.toggle();
    delay(1000);

}