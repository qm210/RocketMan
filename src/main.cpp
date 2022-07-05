#include <Arduino.h>
// #include <WiFi.h>
// #include <AsyncElegantOTA.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <memory>
#include "main.h"
#include "utils.h"
#include "patterns.h"
#include "PatternBase.h"
#include "RocketManager.h"

/*
const char* ssid = "ROCKET_NET";
const char* password = "rakete";
AsyncWebServer server(80);
*/

unsigned long time_ms;

CRGB master_leds[NUM_STRIPS][NUM_LEDS];

PatternBase *theRainbowOscillation = new RainbowOscillation();
PatternBase *theWhiteGlitter = new WhiteGlitter();

PatternBase* allPatterns[] = {
    theRainbowOscillation,
    theWhiteGlitter,
};

RocketManager rocketManager;

/*
void setupOTA() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello dear sir.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}
*/

void setup() {
    // setupOTA(); // can't seem to manage right now

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