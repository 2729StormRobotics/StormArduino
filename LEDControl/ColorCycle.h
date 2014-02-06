#ifndef COLOR_CYCLE_H
#define COLOR_CYCLE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class ColorCycle : public LEDMode {

    uint8_t delayCounter;

    public:
        ColorCycle() : delayCounter(0) {}
        void doLoop(){
            if (delayCounter == 0) {
                for (uint8_t i = 0; i < NUM_LEDS; i++){
                    switch (random(7)){
                        case 0:  leds[i] = WHITE;
                                 break;
                        case 1:  leds[i] = RED;
                                 break;
                        case 2:  leds[i] = GREEN;
                                 break;
                        case 3:  leds[i] = BLUE;
                                 break;
                        case 4:  leds[i] = YELLOW;
                                 break;
                        case 5:  leds[i] = MAGENTA;
                                 break;
                        case 6:  leds[i] = CYAN;
                                 break;
                        default: break;
                    }
                }
            }

            delayCounter++;
            delayCounter %= 50; //Cycle once per second
        }
        void reset(){
            delayCounter = 0;
        }
};

#endif
