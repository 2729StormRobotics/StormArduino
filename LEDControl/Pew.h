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
            case 0:  currentColor = CRGB::White;
                     break;
            case 1:  currentColor = CRGB::Red;
                     break;
            case 2:  currentColor = CRGB::Green;
                     break;
            case 3:  currentColor = CRGB::Blue;
                     break;
            default: break;
        }

        for (int i = 0; i < NUM_LEDS; i++){
            if (i == (NUM_LEDS / 2 - 1) - count || i == (NUM_LEDS / 2) + count) leds[i] = currentColor;
            else                                                                leds[i] = CRGB::Black;
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
