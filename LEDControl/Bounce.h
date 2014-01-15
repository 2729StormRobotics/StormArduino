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

        switch (colorCounter){
            case 0:  currentColor = WHITE;
                     break;
            case 1:  currentColor = RED;
                     break;
            case 2:  currentColor = GREEN;
                     break;
            case 3:  currentColor = BLUE;
                     break;
            default: break;
        }

        for (int i = 0; i < NUM_LEDS; i++){
            if (i == (NUM_LEDS / 2 - 1) - count || i == (NUM_LEDS / 2) + count) leds[i] = currentColor;
            else                                                                leds[i] = BLACK;
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
        direc        = 0;
    }

};

#endif
