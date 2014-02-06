#ifndef COLLAPSE_H
#define COLLAPSE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Collapse : public LEDMode {
    
    uint8_t posCounter;
    uint8_t noTouch;
    CRGB color1, color2;
  
    public:
        Collapse() : posCounter(0), noTouch(0), color1(BLACK), color2(BLACK) {}
        void doLoop(){
            if (posCounter == 0){
                color1 = leds[NUM_LEDS / 2 - 1 - noTouch];
                color2 = leds[NUM_LEDS / 2 + noTouch];
            }
            for (uint8_t i = 0; i < NUM_LEDS; i++){ 
                if (i >= NUM_LEDS / 2 - 1 - noTouch && i <= NUM_LEDS / 2 + noTouch){
                    if (i == NUM_LEDS / 2 - 1 - noTouch + posCounter)  leds[i] = color1;
                    else if (i == NUM_LEDS / 2 + noTouch - posCounter) leds[i] = color2;
                    else                                               leds[i] = BLACK;
                }
            }
            
            posCounter++;
            posCounter %= noTouch + 1;
            
            if (posCounter == 0){
                noTouch++;
                noTouch %= (NUM_LEDS / 2);
                
                if (noTouch == 0){
                    for (uint8_t i = 0; i < NUM_LEDS; i++){
                        leds[i].r = random(128);
                        leds[i].g = random(128);
                        leds[i].b = random(128);
                    }
                }
            }
        }
        void reset(){
            posCounter = 0;
            noTouch = 0;
            for (uint8_t i = 0; i < NUM_LEDS; i++){
                leds[i].r = random(128);
                leds[i].g = random(128);
                leds[i].b = random(128);
            }
        }
        
};

#endif
