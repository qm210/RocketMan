#pragma once

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
