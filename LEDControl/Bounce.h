#ifndef BOUNCE_H
#define BOUNCE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Bounce : public LEDMode {
    int count        = 0;
    int colorCounter = 0;
    int direc        = 1;

    public:
    void doLoop() {

        CRGB currentColor;
        CRGB nextColor;

        switch (colorCounter){
            case 0:  currentColor = WHITE;
                     nextColor = RED;
                     break;
            case 1:  currentColor = RED;
                     nextColor = GREEN;
                     break;
            case 2:  currentColor = GREEN;
                     nextColor = BLUE;
                     break;
            case 3:  currentColor = BLUE;
                     nextColor = WHITE;
                     break;
            default: break;
        }

        for (int i = 0; i < NUM_LEDS; i++){
            if      (i == count)            leds[i] = currentColor;
            else if (i == NUM_LEDS - count) leds[i] = nextColor;
            else                            leds[i] = BLACK;
        }
        

        count += direc;

        if (count == 0) {
            direc = 1;
            colorCounter++;
            colorCounter %= 4;
        }
        else if (count == (NUM_LEDS / 2 - 1)) direc = -1;
    }
    void reset(){
        count        = 0;
        colorCounter = 0;
        direc        = 1;
    }

};

#endif
