#ifndef MARQUEE_H
#define MARQUEE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Marquee : public LEDMode {
    int count        = 0;
    int delayCounter = 0;

    public:
        void doLoop(){
            if (delayCounter == 0){
                for (int i = 0; i < NUM_LEDS; i++){
                    if ((i + count) % 3 != 0) leds[i] = CRGB::Black;
                    else {
                        switch (random(4)){
                            case 0:  leds[i] = CRGB::White;
                                     break;
                            case 1:  leds[i] = CRGB::Red;
                                     break;
                            case 2:  leds[i] = CRGB::Green;
                                     break;
                            case 3:  leds[i] = CRGB::Blue;
                                     break;
                            default: break;
                        }
                    }
                }

                count++;
                count %= 3;
            }

            delayCounter++;
            delayCounter %= 10; //Cycle every 10 cycles, or 5 times a second
        }
        void reset(){
            count        = 0;
            delayCounter = 0;
        }
};

#endif
