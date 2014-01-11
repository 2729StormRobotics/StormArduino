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
                    case 0:  leds[i] = CRGB::White;
                             break;
                    case 1:  leds[i] = CRGB::Red;
                             break;
                    case 2:  leds[i] = CRGB::Green;
                             break;
                    case 3:  leds[i] = CRGB::Blue;
                             break;
                    case 4:  leds[i] = CRGB::Yellow;
                             break;
                    case 5:  leds[i] = CRGB::Magenta;
                             break;
                    case 6:  leds[i] = CRGB::Cyan;
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
