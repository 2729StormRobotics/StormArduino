#ifndef COLOR_CYCLE_H
#define COLOR_CYCLE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class ColorCycle : public LEDMode {
    int count        = 0;
    int delayCounter = 0;

    public:
    void doLoop(){
        if (delayCounter == 0) {
            for (int i = 0; i < NUM_LEDS; i++){
                switch (count){
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
            count++;
            count %= 7;
        }

        delayCounter++;
        delayCounter %= 50; //Cycle once per second
    }
    void reset(){
        count        = 0;
        delayCounter = 0;
    }
};

#endif
