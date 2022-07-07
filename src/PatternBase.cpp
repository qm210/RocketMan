#include "main.h"
#include "PatternBase.h"

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
