#ifndef ONEWAYPILE_H
#define ONEWAYPILE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class OneWayPile : public LEDMode {
    int count;
    int noTouch;
    int colorCounter;
    CRGB color;
    CRGB prevColor;

    public:
        OneWayPile() : count(0), noTouch(0), colorCounter(0), color(RED), prevColor(BLACK) {}
        void doLoop(){
            for (int i = 0; i < NUM_LEDS; i++){
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
                        case 1: color = ORANGE;
                                prevColor = RED;
                                break;
                        case 2: color = YELLOW;
                                prevColor = ORANGE;
                                break;
                        case 3: color = GREEN;
                                prevColor = YELLOW;
                                break;
                        case 4: color = BLUE;
                                prevColor = GREEN;
                                break;
                        case 5: color = PURPLE;
                                prevColor = BLUE;
                                break;
                        case 6: color = WHITE;
                                prevColor = PURPLE;
                                break;
                        case 7: color = CYAN;
                                prevColor = WHITE;
                                break;
                        case 8: color = BLACK;
                                prevColor = CYAN;
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
