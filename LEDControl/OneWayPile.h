#ifndef ONEWAYPILE_H
#define ONEWAYPILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class OneWayPile : public LEDMode {
    uint8_t count;
    uint8_t noTouch;
    uint8_t colorCounter;
    CRGB color;
    CRGB prevColor;

    public:
        OneWayPile() : count(0), noTouch(0), colorCounter(0), color(RED), prevColor(BLACK) {}
        void doLoop(){
            for (uint8_t i = 0; i < NUM_LEDS; i++){
                if (i >= noTouch){
                    if (i == NUM_LEDS - 1 - count) leds[i] = color;
                    else                           leds[i] = prevColor;
                }
            }

            count++;
            count %= NUM_LEDS - noTouch;

            if (count == 0){
                noTouch++;
                noTouch %= (NUM_LEDS - 1);
                
                if (noTouch == 0){
                    colorCounter++;
                    colorCounter %= 9;
                    switch(colorCounter){
                        case 0: color = RED;
                                prevColor = BLACK;
                                break;
                        case 1: color = GREEN;
                                prevColor = RED;
                                break;
                        case 2: color = BLUE;
                                prevColor = GREEN;
                                break;
                        case 3: color = YELLOW;
                                prevColor = BLUE;
                                break;
                        case 4: color = PURPLE;
                                prevColor = YELLOW;
                                break;
                        case 5: color = CYAN;
                                prevColor = PURPLE;
                                break;
                        case 6: color = WHITE;
                                prevColor = CYAN;
                                break;
                        case 7: color = ORANGE;
                                prevColor = WHITE;
                                break;
                        case 8: color = BLACK;
                                prevColor = ORANGE;
                                break;
                    }
                }
            }
        }
        void reset(){
            count = 0;
            noTouch = 0;
        }
};

#endif
