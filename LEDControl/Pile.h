#ifndef PILE_H
#define PILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Pile : public LEDMode {
    int count;
    int noTouch;
    CRGB color;

    public:
        Pile() : count(0), noTouch(0), color(RED) {}
        void doLoop(){
            for (int i = 0; i < NUM_LEDS; i++){
                if (i >= noTouch && i < NUM_LEDS - noTouch){
                    
                    if (i == (NUM_LEDS / 2 - 1) - count || i == (NUM_LEDS / 2) + count) leds[i] = color;
                    else                                                                leds[i] = BLACK;
                }
            }

            count++;
            count %= (NUM_LEDS / 2) - noTouch;

            if (count == 0){
                noTouch++;
                noTouch %= (NUM_LEDS / 2 - 1);
                color.r = random(128);
                color.g = random(128);
                color.b = random(128);
            }
        }
        void reset(){
            count = 0;
            noTouch = 0;
        }
};

#endif
