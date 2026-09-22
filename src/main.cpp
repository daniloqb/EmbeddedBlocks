#include <Arduino.h>
#include <EmbeddedBlocks.h>

eb::LedRGB led(9, 10, 11);
eb::Button button(2);

eb::ButtonEvent buttonEvent;

void setup()
{
    led.begin();
    led.setHue(0);
    led.on();
    led.setBrightness(100);
    led.setSaturation(100);

    button.begin();

    Serial.begin(9600);
}

void loop()
{

    button.update();

    buttonEvent = button.getEvent();
    
    switch (buttonEvent)
    {
        case eb::ButtonEvent::PRESSED:
            Serial.println("PRESSED");
            break;
        case eb::ButtonEvent::RELEASED:
            Serial.println("RELEASED");
            break;
        case eb::ButtonEvent::HELD_START:
            Serial.println("HELD_START");
            break;
        default:
            break;
    }
    // switch (button.getState())
    // {
    //     case eb::ButtonState::UP:
    //         Serial.println("UP");
    //         break;
    //     case eb::ButtonState::DOWN:
    //         Serial.println("DOWN");
    //         break;
    //     case eb::ButtonState::HELD:
    //         Serial.println("HELD");
    //         break;
    //     default:
    //         break;
    // }
}