#include <Arduino.h>
#include <FastLED.h>
#include <memory>
#include "main.h"
#include "utils.h"
#include "patterns.h"
#include "PatternBase.h"
#include "RocketManager.h"

unsigned long time_ms;

CRGB master_leds[NUM_STRIPS][NUM_LEDS];

PatternBase *theRainbowOscillation = new RainbowOscillation();
PatternBase *theWhiteGlitter = new WhiteGlitter();

PatternBase* allPatterns[] = {
    theRainbowOscillation,
    theWhiteGlitter,
};

RocketManager rocketManager;

void setup() {
    FastLED.addLeds<LED_TYPE, PIN_DATA0, PIN_CLOCK0, COLOR_ORDER>(master_leds[0], NUM_LEDS);
    FastLED.addLeds<LED_TYPE, PIN_DATA1, PIN_CLOCK1, COLOR_ORDER>(master_leds[1], NUM_LEDS);
    FastLED.addLeds<LED_TYPE, PIN_DATA2, PIN_CLOCK2, COLOR_ORDER>(master_leds[2], NUM_LEDS);
    FastLED.addLeds<LED_TYPE, PIN_DATA3, PIN_CLOCK3, COLOR_ORDER>(master_leds[3], NUM_LEDS);
    FastLED.addLeds<LED_TYPE, PIN_DATA4, PIN_CLOCK4, COLOR_ORDER>(master_leds[4], NUM_LEDS);

    FastLED.setBrightness(GLOBAL_BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 900);
    FastLED.clear();
    FastLED.show();

    time_ms = millis();

    Serial.begin(115200);
    Serial.println("Start.");

    theRainbowOscillation->brightness = 255;
    theRainbowOscillation->fade_factor = 255;
    theRainbowOscillation->frame_delay_ms = 3;

    rocketManager.setup();
}

void advance(unsigned long delta_ms) {

    MasterLoop([](int s, int i) {
        master_leds[s][i] = CRGB::Black;
    });

    for (auto &pattern : allPatterns) {
        pattern->process(delta_ms);

        MasterLoop([pattern](int s, int l) {
            master_leds[s][l] += pattern->get(s, l);
        });
    }

    // color correction / "mastering". y tho?
    // MasterLoop([](int s, int l) {
    //     // auto lumi = master_leds[s][l].getLuma();
    //     master_leds[s][l].g *= 0.3;
    // });

    FastLED.show();
}

void loop() {
    auto delta_ms = millis() - time_ms;
    time_ms = millis();
    advance(delta_ms);

    EVERY_N_MINUTES(2) {
        rocketManager.store();
    }
}