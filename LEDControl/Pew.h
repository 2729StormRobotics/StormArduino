#ifndef PEW_H
#define PEW_H

#include "commonIncludes.h"
#include "Pew.h"

class Pew : public LEDMode {
  
    uint8_t posCounter;
    uint8_t colorCounter;

    public:
        Pew() : posCounter(0), colorCounter(0) {}
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

            for (uint8_t i = 0; i < NUM_LEDS; i++){
                if (i == NUM_LEDS / 2 - 1 - posCounter || i == NUM_LEDS / 2 + posCounter) leds[i] = currentColor;
                else                                                                      leds[i] = BLACK;
            }

            posCounter++;
            posCounter %= (NUM_LEDS / 2);

            if (posCounter == 0) {
                colorCounter++;
                colorCounter %= 4;
            }
        }
        void reset(){
            posCounter   = 0;
            colorCounter = 0;
        }
};

#endif
