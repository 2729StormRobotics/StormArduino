#ifndef ONEWAYPILE_H
#define ONEWAYPILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class OneWayPile : public LEDMode {
  
    uint8_t posCounter;
    uint8_t noTouch;
    uint8_t colorCounter;
    CRGB color;
    CRGB prevColor;

    public:
        OneWayPile() : posCounter(0), noTouch(0), colorCounter(0), color(RED), prevColor(BLACK) {}
        void doLoop(){
            for (uint8_t i = 0; i < NUM_LEDS; i++){
                if (i >= noTouch){
                    if (i == NUM_LEDS - 1 - posCounter) leds[i] = color;
                    else                                leds[i] = prevColor;
                }
            }

            posCounter++;
            posCounter %= NUM_LEDS - noTouch;

            if (posCounter == 0){
                noTouch++;
                noTouch %= (NUM_LEDS - 1);
                
                if (noTouch == 0){
                  
                    colorCounter++;
                    colorCounter %= 9;
                    
                    prevColor = color;
                    
                    switch(colorCounter){
                        case 0: color = RED;
                                break;
                        case 1: color = GREEN;
                                break;
                        case 2: color = BLUE;
                                break;
                        case 3: color = YELLOW;
                                break;
                        case 4: color = CYAN;
                                break;
                        case 5: color = PURPLE;
                                break;
                        case 6: color = WHITE;
                                break;
                        case 7: color = ORANGE;
                                break;
                        case 8: color = BLACK;
                                break;
                    }
                }
            }
        }
        void reset(){
            posCounter = 0;
            noTouch    = 0;
        }
};

#endif
