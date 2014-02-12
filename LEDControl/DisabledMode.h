#ifndef FLASH_WHITE_H
#define FLASH_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class DisabledMode : public LEDMode {
  
    uint8_t section; //0 - going to red
                     //1 - going to orange
                     //2 - going to black
    uint8_t delayCounter;
    uint8_t delayMax;
    CRGB color;
    
    public:
        DisabledMode(): section(0),color(BLACK), delayCounter(0), delayMax(1) {}
        void doLoop(){
            if (delayCounter == 0){
                if (section == 0){
                    if (color.r < ORANGE.r){
                        color.r += 1;
                    } else {
                        section = 1;
                        color.r = 255;
                        delayMax = 5;
                    }
                } else if (section == 1){
                    if (color.g < ORANGE.g){
                        color.g += 1;
                    } else {
                        color.g = ORANGE.g;
                        section = 2;
                    }
                } else {
                    if (color.g > 1){
                        color.g -= 1;
                    } else {
                        color.g = 0;
                        section = 1;
                    }
                }
                
                for (int i = 0; i < NUM_LEDS; i++){
                    leds[i] = color;
                }
            }
            
            delayCounter++;
            delayCounter %= delayMax; //start at full speed, then go to half
        }
        
        void reset(){
            for (int i = 0; i < NUM_LEDS; i++){
                leds[i] = color;
            }
        }
};

#endif
