#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

#include <cstdint>

#define NUM_LEDS 80
#define DATA_PIN  8
#define CLOCK_PIN 9
CRGB leds[NUM_LEDS];

CRGB RED     = CRGB::Red;
CRGB ORANGE  = 0xFF1600;
CRGB YELLOW  = 0xFF6400;
CRGB GREEN   = CRGB::Green;
CRGB BLUE    = CRGB::Blue;
CRGB PURPLE  = CRGB::Purple;
CRGB BLACK   = CRGB::Black;
CRGB WHITE   = CRGB::White;
CRGB MAGENTA = CRGB::Magenta;
CRGB CYAN    = CRGB::Cyan;

#endif
