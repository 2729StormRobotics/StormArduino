#ifndef USA_H
#define USA_H

#include "commonIncludes.h"
#include "LEDMode.h"

class USAMode : public LEDMode {
  
    uint8_t colorCounter;
    uint8_t delayCounter;
    uint8_t topLED;

    public:
        USAMode() : colorCounter(0), delayCounter(0), topLED(0) {}
        void doLoop(){
            if (delayCounter == 0){
              
                for (uint8_t i = topLED; i > 0; i--){
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

            delayCounter++;
            delayCounter %= 5;
        }
        void reset(){
            colorCounter = 0;
            topLED       = 0;
            delayCounter = 0;
        }
};

#endif
