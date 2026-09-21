#include <EmbeddedBlocks/hardware/LedRGB.h>
#include <Arduino.h>
#include <math.h>

namespace eb
{

    LedRGB::LedRGB(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
        : m_red(redPin),
          m_green(greenPin),
          m_blue(bluePin),
          m_Rvalue(0),
          m_Gvalue(0),
          m_Bvalue(0),
          m_brightness(100),
          m_saturation(100),
          m_hue(0),
          m_state(false)
    {
    }

    void LedRGB::begin()
    {
        m_red.begin();
        m_green.begin();
        m_blue.begin();

        applyColor();
    }

    // ---------------------------------------------------------
    // RGB
    // ---------------------------------------------------------

    void LedRGB::setColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_Rvalue = red;
        m_Gvalue = green;
        m_Bvalue = blue;

        // Como o usuário definiu a cor diretamente em RGB,
        // atualizamos o Hue correspondente.
        m_hue = rgbToHue(red, green, blue);

        applyColor();
    }

    // ---------------------------------------------------------
    // HUE
    // ---------------------------------------------------------

    void LedRGB::setHue(uint16_t hue)
    {
        // Garante o comportamento circular:
        // 360 -> 0
        // 420 -> 60
        // 720 -> 0
        m_hue = hue % 360;

        updateColorFromHSV();
    }

    // ---------------------------------------------------------
    // SATURATION
    // ---------------------------------------------------------

    void LedRGB::setSaturation(uint8_t saturation)
    {
        m_saturation = constrain(saturation, 0, 100);

        // A saturação mudou, portanto precisamos recalcular
        // o RGB mantendo o Hue atual.
        updateColorFromHSV();
    }

    // ---------------------------------------------------------
    // BRIGHTNESS
    // ---------------------------------------------------------

    void LedRGB::setBrightness(uint8_t brightness)
    {
        m_brightness = constrain(brightness, 0, 100);

        // Brightness não altera a cor armazenada.
        // Apenas altera a intensidade enviada ao PWM.
        applyColor();
    }

    uint8_t LedRGB::getBrightness()
    {
        return m_brightness;
    }

    // ---------------------------------------------------------
    // ON / OFF
    // ---------------------------------------------------------

    void LedRGB::on()
    {
        m_state = true;

        applyColor();
    }

    void LedRGB::off()
    {
        m_state = false;

        applyColor();
    }

    void LedRGB::toggle()
    {
        if (m_state)
        {
            off();
        }
        else
        {
            on();
        }
    }

    // =========================================================
    // PRIVATE
    // =========================================================

    // ---------------------------------------------------------
    // HSV -> RGB
    // ---------------------------------------------------------

    void LedRGB::updateColorFromHSV()
    {
        float r;
        float g;
        float b;

        // Saturação da API:
        // 0..100
        //
        // Saturação usada pela fórmula:
        // 0.0..1.0
        float s = m_saturation / 100.0f;

        // O brightness NÃO entra aqui.
        // Ele será aplicado depois em applyColor().
        float v = 1.0f;

        float c = v * s;

        float x = c *
                  (1.0f -
                   abs(fmod(m_hue / 60.0f, 2.0f) - 1.0f));

        float m = v - c;

        // Descobre em qual dos seis setores
        // do círculo de cores estamos.
        if (m_hue < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (m_hue < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (m_hue < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (m_hue < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (m_hue < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }

        // Converte de 0.0..1.0 para 0..255.
        //
        // IMPORTANTE:
        // não usamos setColor() aqui.
        //
        // Se usássemos, setColor() tentaria calcular
        // novamente o Hue a partir do RGB.
        m_Rvalue = static_cast<uint8_t>((r + m) * 255.0f);
        m_Gvalue = static_cast<uint8_t>((g + m) * 255.0f);
        m_Bvalue = static_cast<uint8_t>((b + m) * 255.0f);

        applyColor();
    }

    // ---------------------------------------------------------
    // Envia a cor para o hardware
    // ---------------------------------------------------------

    void LedRGB::applyColor()
    {
        if (!m_state)
        {
            m_red.write(0);
            m_green.write(0);
            m_blue.write(0);

            return;
        }

        m_red.write(
            (static_cast<uint32_t>(m_Rvalue) * m_brightness) / 100
        );

        m_green.write(
            (static_cast<uint32_t>(m_Gvalue) * m_brightness) / 100
        );

        m_blue.write(
            (static_cast<uint32_t>(m_Bvalue) * m_brightness) / 100
        );
    }

    // ---------------------------------------------------------
    // RGB -> HUE
    // ---------------------------------------------------------

    uint16_t LedRGB::rgbToHue(
        uint8_t red,
        uint8_t green,
        uint8_t blue)
    {
        float r = red / 255.0f;
        float g = green / 255.0f;
        float b = blue / 255.0f;

        float maxValue = fmax(r, fmax(g, b));
        float minValue = fmin(r, fmin(g, b));

        float delta = maxValue - minValue;

        // Branco, cinza e preto não possuem Hue definido.
        //
        // Nesse caso mantemos o Hue que já estava selecionado.
        if (delta == 0.0f)
        {
            return m_hue;
        }

        float hue;

        if (maxValue == r)
        {
            hue =
                60.0f *
                fmod(((g - b) / delta), 6.0f);
        }
        else if (maxValue == g)
        {
            hue =
                60.0f *
                (((b - r) / delta) + 2.0f);
        }
        else
        {
            hue =
                60.0f *
                (((r - g) / delta) + 4.0f);
        }

        if (hue < 0.0f)
        {
            hue += 360.0f;
        }

        return static_cast<uint16_t>(hue);
    }

    void LedRGB::randomHue()
    {
        uint16_t hue = static_cast<uint16_t>(random(0, 361));
        setHue(hue);
    }

}