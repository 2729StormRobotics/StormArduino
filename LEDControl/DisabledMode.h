#ifndef FLASH_WHITE_H
#define FLASH_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class DisabledMode : public LEDMode {
    bool on;
    uint8_t delayCount;
    CRGB allianceColor;
    
    static const byte allianceBlue       = 0; //Because I don't trust enums to be bytes
    static const byte allianceRed        = 1;
    static const byte allianceInvalid    = 2;
    static const byte allianceRobotError = 3;

    public:
        DisabledMode() : on(true), delayCount(0), allianceColor(GREEN) {} //start out as an error to indicate the robot sent nothing
        void doLoop() {
            if (delayCount == 0){
                for (uint8_t i = 0; i < NUM_LEDS; i++) {
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
               case allianceBlue:       allianceColor = BLUE;
                                        break;
               case allianceRed:        allianceColor = RED;
                                        break;
               case allianceInvalid:    allianceColor = PURPLE;
                                        break;
               case allianceRobotError: allianceColor = ORANGE;
                                        break;
               default:                 allianceColor = GREEN;
                                        break;
            }
            Serial.println(alliance);
        }
};

#endif
