#ifndef MARQUEE_H
#define MARQUEE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Marquee : public LEDMode {
  
    uint8_t posCounter;
    uint8_t delayCounter;
    uint8_t colorCounter;
    uint8_t topLED;

    public:
        Marquee() : posCounter(0), delayCounter(0), colorCounter(0), topLED(0) {}
        void doLoop(){
            if (delayCounter == 0){
                for (uint8_t i = topLED; i > 0; i--){
                    leds[i] = leds[i - 1];
                }
                if (posCounter % 3 != 0) leds[0] = BLACK;
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
                    
                    colorCounter++;
                    colorCounter %= 4;
                }

                posCounter++;
                posCounter %= 3;
                
                if (topLED < NUM_LEDS - 1){
                    topLED++;
                }
            }

            delayCounter++;
            delayCounter %= 5; //Cycle every 5 cycles, or 10 times a second
        }
        void reset(){
            posCounter   = 0;
            delayCounter = 0;
            topLED       = 0;
            colorCounter = 0;
        }
};

#endif
