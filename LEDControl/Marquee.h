#ifndef MARQUEE_H
#define MARQUEE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Marquee : public LEDMode {
    int count        = 0;
    int delayCounter = 0;
    int colorCounter = 0;

    public:
        void doLoop(){
            if (delayCounter == 0){
                for (int i = NUM_LEDS; i > 0; i--){
                    leds[i] = leds[i - 1];
                }
                if (count % 3 != 0) leds[0] = BLACK;
                else {
                    switch (colorCounter){
                            case 0:  leds[0] = WHITE;
                                     break;
                            case 1:  leds[0] = RED;
                                     break;
                            case 2:  leds[0] = GREEN;
                                     break;
                            case 3:  leds[0] = BLUE;
                                     break;
                            default: break;
                    }
                }

                count++;
                count %= 3;

                colorCounter++;
                colorCounter %= 4;
            }

            delayCounter++;
            delayCounter %= 5; //Cycle every 5 cycles, or 10 times a second
        }
        void reset(){
            count        = 0;
            delayCounter = 0;
        }
};

#endif
