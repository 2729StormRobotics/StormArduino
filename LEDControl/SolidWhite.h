#ifndef SOLID_WHITE_H
#define SOLID_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class SolidWhite : public LEDMode {
    public:
        void doLoop() {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::White;
            }
        }
        void reset() {};
};

#endif
