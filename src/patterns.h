#ifndef PATTERNS_H
#define PATTERNS_H

#include <Arduino.h>
#include <FastLED.h>
#include "PatternBase.h"
#include "main.h"

template <typename Func>
inline void apply_around(int center, int width, Func apply) {
    for (int k = -width; k <= width; k++) {
        int pixel = center + k;
        if (pixel < 0 || pixel >= NUM_LEDS)
            continue;
        apply(center, k);
    }
}

// TODO: intensity corrected colors
#define GLOW_NEIGHBORS 10

/*
void sin_glow(CRGB leds[], double time) {
    auto center_pixel = NUM_LEDS * 0.5 * (1. + sin(10. * time));
    for (int k = -GLOW_NEIGHBORS; k <= GLOW_NEIGHBORS; k++) {
        auto pixel = (int)(center_pixel + k);
        if (pixel < 0 || pixel >= NUM_LEDS)
            continue;

        auto intensity = 255 * exp(-(k*k) * 0.1);
        leds[pixel] = CHSV(0, intensity, 0);
    }
}

void red_glow(CRGB leds[]) {
    if (random8() > 10) {
        return;
    }
    auto center = random16(NUM_LEDS);
    auto width = random8(6);
    apply_around(center, width, [leds, width](int c, int k) {
        auto value = leds[c + k];
        double intensity = exp(-(k*k) / width / width);

        value.r = qadd8(value.r, 200 * intensity * intensity);
        leds[c + k] = value;
    });
}
*/

struct RainbowOscillation : PatternBase
{
public:
    void render(int strip_index) override {
        int step = count_ms / 20;
        int somepixel = triangle_modulo(step, NUM_LEDS);
        leds[strip_index][somepixel] = CHSV(hue, 255, 255);

        if (step % 100 == 0) {
            hue = (hue + random8(0, 6) * random8(-10, 10)) % 255;
        }
    }

private:
    uint8_t hue = 0;
};

struct WhiteGlitter : PatternBase
{
public:
    uint8_t spawn_threshold = 50;

    void render(int strip_index) override {
        if (random8() < spawn_threshold) {
            leds[strip_index][random16(NUM_LEDS)] += CRGB::White;
        }
    }
};

#endif