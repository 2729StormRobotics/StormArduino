#ifndef USA_H
#define USA_H

#include "commonIncludes.h"
#include "LEDMode.h"

class USAMode : public LEDMode {
    int colorCounter = 0;
    int count = 0;

    public:
        void doLoop(){
            if (count == 0){
                for (int i = NUM_LEDS; i > 0; i--){
                    leds[i] = leds[i - 1];
                }
                switch (colorCounter){
                    case 0:  leds[0] = RED;
                             break;
                    case 1:  leds[0] = WHITE;
                             break;
                    case 2:  leds[0] = BLUE;
                             break;
                    default: break;
                }

                colorCounter++;
                colorCounter %= 3;
            }

            count++;
            count %= 5;
        }
        void reset(){
            colorCounter = 0;
        }
};

#endif
