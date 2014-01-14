#ifndef PEW_H
#define PEW_H

#include "commonIncludes.h"
#include "Pew.h"

class Pew : public LEDMode {
    int count        = 0;
    int colorCounter = 0;

    public:
    void doLoop() {

        long currentColor;

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

        count++;
        count %= (NUM_LEDS / 2 - 1);

        if (count == 0) {
            colorCounter++;
            colorCounter %= 4;
        }
    }
    void reset(){
        count        = 0;
        colorCounter = 0;
    }

};

#endif
