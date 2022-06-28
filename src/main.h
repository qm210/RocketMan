#pragma once

#include <FastLED.h>

#define LED_TYPE SK9822
#define COLOR_ORDER BGR
#define NUM_LEDS 300

#define NUM_STRIPS 1
#define PIN_DATA0 12
#define PIN_CLOCK0 14
#define PIN_DATA1 TODO
#define PIN_CLOCK1 TODO
#define PIN_DATA2 TODO
#define PIN_CLOCK2 TODO
#define PIN_DATA3 TODO
#define PIN_CLOCK3 TODO
#define PIN_DATA4 TODO
#define PIN_CLOCK4 TODO

// 300 LEDS with 1 hue on brightness 20 reached about 0.8 A total via USB (also, voltage drop from 4.2V at source to about 3.4V)
#define GLOBAL_BRIGHTNESS 10

template <typename Func>
inline void MasterLoop(Func f) {
    for (int s=0; s < NUM_STRIPS; s++)
        for (int i=0; i < NUM_LEDS; i++)
            f(s, i);
}
