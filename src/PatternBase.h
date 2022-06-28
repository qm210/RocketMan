#pragma once

#include <FastLED.h>
#include "main.h"

struct PatternBase
{
public:
    uint8_t brightness = 255;
    uint8_t fade_factor = 240;
    uint16_t frame_delay_ms = 10;

    PatternBase() { }

    CRGB get(int strip_index, int led_index);
    void process(int delta_ms);
    virtual void render(int strip_index) = 0;
    // something like "blend mode"?

protected:
    CRGB leds[NUM_STRIPS][NUM_LEDS];
    long count_ms = 0;
};

CRGB PatternBase::get(int strip_index, int led_index) {
    return leds[strip_index][led_index].scale8(brightness);
}

void PatternBase::process(int delta_ms) {
    count_ms += delta_ms;
    if (count_ms < frame_delay_ms)
        return;

    for (int s=0; s < NUM_STRIPS; s++) {
        for (int i=0; i < NUM_LEDS; i++) {
            leds[s][i].nscale8(fade_factor);
        }
        render(s);
    }

    count_ms -= frame_delay_ms;
}
