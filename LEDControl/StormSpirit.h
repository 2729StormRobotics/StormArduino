#ifndef STORM_SPIRIT_H
#define STORM_SPIRIT_H

#include "commonIncludes.h"
#include "LEDMode.h"

class StormSpirit : public LEDMode {
  
    uint8_t delayCounter;
    uint8_t posCounter;

    public:
        StormSpirit() : delayCounter(0), posCounter(0) {}
        void doLoop(){
            if (delayCounter == 0){
                for (uint8_t i = 0; i < NUM_LEDS; i++){
                    if      ((i + posCounter) % 4 == 0)  leds[i] = ORANGE;
                    else if ((i + posCounter) % 4 == 2)  leds[i] = RED;
                    else                                 leds[i] = BLACK;
                }

                posCounter++;
                posCounter %= 4;
            }

            delayCounter++;
            delayCounter %= 5;
        }
        void reset(){
            delayCounter = 0;
            posCounter   = 0;
        }
};

#endif
