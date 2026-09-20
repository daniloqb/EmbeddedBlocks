#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::RGBLed led(9, 10, 11);

uint16_t hue = 0;

void setup()
{
    led.begin();
    led.off();
    led.setColor(255, 255, 255);
    led.on();
    delay(1000);
    led.setBrightness(100);
    led.setSaturation(100);

}

void loop()
{
    led.setHue(hue);
    hue = (hue + 1) % 360;
    delay(1000);

}