#ifndef USA_H
#define USA_H

#include "commonIncludes.h"
#include "LEDMode.h"

class USAMode : public LEDMode {
    int colorCounter;
    int count;
    int topLED;

    public:
        USAMode() : colorCounter(0), count(0), topLED(0) {}
        void doLoop(){
            if (count == 0){
                for (int i = topLED; i > 0; i--){
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

                if (topLED < NUM_LEDS - 1){
                    topLED++;
                }
            }

            count++;
            count %= 5;
        }
        void reset(){
            colorCounter = 0;
            topLED       = 0;
        }
};

#endif
