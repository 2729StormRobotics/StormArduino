#ifndef PILE_H
#define PILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Pile : public LEDMode {
    int count   = 0;
    int noTouch = 0;

    void doLoop(){
        for (int i = 0; i < NUM_LEDS; i++){
            if (i >= noTouch && i < NUM_LEDS - noTouch){
                if (i == (NUM_LEDS / 2 - 1) - count || i == (NUM_LEDS / 2) + count) leds[i] = WHITE;
                else                                                                leds[i] = BLACK;
            }
        }

        count++;
        count %= (NUM_LEDS / 2) - noTouch;

        if (count == 0){
            noTouch++;
            noTouch %= (NUM_LEDS / 2 - 1);
        }
    }
    void reset(){
        count = 0;
        noTouch = 0;
    }
};

#endif
