#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::RGBLed led(9, 10, 11);

void setup()
{
    led.begin();
    led.setColor(255, 0, 0); // Set initial color to red
    led.off();
}

void loop()
{
    led.setBrightness(100);
    led.on();
    
    delay(2000);
    led.setColor(0, 255, 0); // Set color to green
    delay(2000);
    led.setColor(0, 0, 255); // Set color to blue
    delay(2000);  
    led.setBrightness(1);
    led.setColor(255, 255, 0); // Set color to white with low brightness    
    delay(2000);
    led.off();
    delay(2000);
}