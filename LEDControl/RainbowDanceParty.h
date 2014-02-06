#ifndef RAINBOW_DANCE_PARTY_H
#define RAINBOW_DANCE_PARTY_H

#include "commonIncludes.h"
#include "LEDMode.h"

class RainbowDanceParty : public LEDMode {
  
    uint8_t colorCounter;
    uint8_t delayCounter;
    uint8_t topLED;

    public:
        RainbowDanceParty() : colorCounter(0), delayCounter(0), topLED(0) {}
        void doLoop(){
            if (delayCounter == 0){
                for (uint8_t i = topLED; i > 0; i--){
                    leds[i] = leds[i - 1];
                }
                switch (colorCounter){
                    case 0:
                    case 1:
                             leds[0] = RED;
                             break;
                    case 2:
                    case 3:
                             leds[0] = ORANGE;
                             break;
                    case 4:
                    case 5:
                             leds[0] = YELLOW;
                             break;
                    case 6:
                    case 7:
                             leds[0] = GREEN;
                             break;
                    case 8:
                    case 9:
                             leds[0] = BLUE;
                             break;
                    case 10:
                    case 11:
                             leds[0] = PURPLE;
                             break;
                    default: break;
                }

                colorCounter++;
                colorCounter %= 12;

                if (topLED < NUM_LEDS - 1){
                    topLED++;
                }
            }

            delayCounter++;
            delayCounter %= 2;

        }
        void reset(){
            colorCounter = 0;
            topLED       = 0;
            delayCounter = 0;
        }
};

#endif
