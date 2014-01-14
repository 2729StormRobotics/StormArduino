#ifndef STORM_SPIRIT_H
#define STORM_SPIRIT_H

#include "commonIncludes.h"
#include "LEDMode.h"

class StormSpirit : public LEDMode {
    int delayCounter = 0;
    int count        = 0;

    public:
        void doLoop(){
            if (delayCounter == 0){
                for (int i = 0; i < NUM_LEDS; i++){
                    if ((i + count) % 4 == 0) leds[i] = ORANGE;
                    else if ((i + count) % 4 == 2)  leds[i] = RED;
                    else leds[i] = BLACK;
                }

                count++;
                count %= 2;
            }

            delayCounter++;
            delayCounter %= 5;
        }
        void reset(){
            delayCounter = 0;
            count        = 0;
        }
};

#endif
