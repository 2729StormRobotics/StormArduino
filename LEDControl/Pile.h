#ifndef PILE_H
#define PILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Pile : public LEDMode {
  
    uint8_t posCounter;
    uint8_t noTouch;
    CRGB color;

    public:
        Pile() : posCounter(0), noTouch(0), color(RED) {}
        void doLoop(){
            for (uint8_t i = 0; i < NUM_LEDS; i++){
                if (i >= noTouch && i < NUM_LEDS - noTouch){
                    if (i == (NUM_LEDS / 2 - 1) - posCounter || i == (NUM_LEDS / 2) + posCounter) leds[i] = color;
                    else                                                                          leds[i] = BLACK;
                }
            }

            posCounter++;
            posCounter %= (NUM_LEDS / 2) - noTouch;

            if (posCounter == 0){
                noTouch++;
                noTouch %= (NUM_LEDS / 2 - 1);
                
                color.r = random(128);
                color.g = random(128);
                color.b = random(128);
            }
        }
        void reset(){
            posCounter = 0;
            noTouch    = 0;
        }
};

#endif
