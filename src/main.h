#pragma once

#include <FastLED.h>

#define LED_TYPE SK9822
#define COLOR_ORDER BGR
#define NUM_LEDS 300

#define NUM_STRIPS 5
#define PIN_DATA0 12
#define PIN_CLOCK0 14
#define PIN_DATA1 27
#define PIN_CLOCK1 26
#define PIN_DATA2 25
#define PIN_CLOCK2 33
#define PIN_DATA3 16
#define PIN_CLOCK3 17
#define PIN_DATA4 18
#define PIN_CLOCK4 19

// 300 LEDS with 1 hue on brightness 20 reached about 0.8 A total via USB (also, voltage drop from 4.2V at source to about 3.4V)
#define GLOBAL_BRIGHTNESS 255

template <typename Func>
inline void MasterLoop(Func f) {
    for (int s=0; s < NUM_STRIPS; s++)
        for (int i=0; i < NUM_LEDS; i++)
            f(s, i);
}
