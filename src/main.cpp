#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::LedRGB led(9, 10, 11);
eb::Button button(2, eb::ButtonConfig::PULLUP);



void setup()
{
    led.begin();
    button.begin();

    led.setHue(0);
    led.on();
    led.setBrightness(100);
    led.setSaturation(100);
}

void loop()
{
    button.update();

    if (button.isPressed())
        led.randomHue();
    delay(100);
}