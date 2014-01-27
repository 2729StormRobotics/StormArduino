#ifndef FLASH_WHITE_H
#define FLASH_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class DisabledMode : public LEDMode {
    bool on;
    int  delayCount;

    public:
        DisabledMode() : on(true), delayCount(0) {}
        void doLoop() {
            if (delayCount == 0){
                for (int i = 0; i < NUM_LEDS; i++) {
                    if (i % 2 == 0) leds[i] = WHITE;
                    else            leds[i] = 0x0000A0;
                }
                on = !on;
            }

            delayCount++;
            delayCount %= 25;
        }
        void reset() {};
};

#endif
