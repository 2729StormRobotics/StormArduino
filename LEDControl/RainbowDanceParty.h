#ifndef RAINBOW_DANCE_PARTY_H
#define RAINBOW_DANCE_PARTY_H

#include "commonIncludes.h"
#include "LEDMode.h"

class RainbowDanceParty : public LEDMode {
    int colorCounter = 0;
    int count        = 0;

    public:
        void doLoop(){
            if (count == 0){
                for (int i = NUM_LEDS; i > 0; i--){
                    leds[i] = leds[i - 1];
                }
                switch (colorCounter){
                    case 0:  leds[0] = RED;
                             break;
                    case 1:  leds[0] = ORANGE;
                             break;
                    case 2:  leds[0] = YELLOW;
                             break;
                    case 3:  leds[0] = GREEN;
                             break;
                    case 4:  leds[0] = BLUE;
                             break;
                    case 5:  leds[0] = PURPLE;
                             break;
                    default: break;
                }
    
                colorCounter++;
                colorCounter %= 6;
            }
            
            count++;
            count %= 2;
        }
        void reset(){
            colorCounter = 0;
        }
};

#endif
