#ifndef FLASH_WHITE_H
#define FLASH_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class DisabledMode : public LEDMode {
    bool on;
    int  delayCount;
    CRGB allianceColor;

    public:
        DisabledMode() : on(true), delayCount(0), allianceColor(BLUE) {} //TODO alliance detection and color changing
        void doLoop() {
            if (delayCount == 0){
                for (int i = 0; i < NUM_LEDS; i++) {
                    if (i % 2 == 0) leds[i] = WHITE;
                    else            leds[i] = allianceColor; 
                }
                on = !on;
            }

            delayCount++;
            delayCount %= 25;
        }
        void reset() {};
        void setAlliance(byte alliance){
            switch (alliance){
               case 0: allianceColor = BLUE;
                       break;
               case 1: allianceColor = RED;
                       break;
               case 2: allianceColor = PURPLE;
                       break;
               case 3: allianceColor = ORANGE;
                       break;
               default: allianceColor = GREEN;
                       break;
            }
            Serial.println(alliance);
        }
};

#endif
