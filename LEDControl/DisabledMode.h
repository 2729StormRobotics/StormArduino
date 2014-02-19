#ifndef FLASH_WHITE_H
#define FLASH_WHITE_H

#include "commonIncludes.h"
#include "LEDMode.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
 * Note: This file contains a lot of hard coding. *
 *       Please don't judge me. It was easier.    *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class DisabledMode : public LEDMode {

    uint8_t delayCounter;
    uint8_t delayMax;
    uint8_t redCounter;
    uint8_t orangeCounter;
    float   sideRedCounter;
    float   sideOrangeCounter;
    int     direc;
    float   sideSpeed;
    
    //23 through 40
    
    public:
        DisabledMode(): delayCounter(0), delayMax(2), redCounter(23), orangeCounter(40), direc(1), sideSpeed(22.0 / 17), sideRedCounter(0), sideOrangeCounter(22) {}
        void doLoop(){
            if (delayCounter == 0){
                
                for (int i = 0; i < NUM_LEDS; i++){
                    if (i == redCounter || i == (int) sideRedCounter || i == (int) (NUM_LEDS - sideRedCounter - 1)){
                        leds[i] = RED;
                        leds[i + 1] = RED;
                        i++;
                    } else if (i == orangeCounter || i == (int) sideOrangeCounter || i == (int) (NUM_LEDS - sideOrangeCounter)) { //No minus 1 because it happens in indeces
                        leds[i] = ORANGE;
                        leds[i - 1] = ORANGE;
                    } else leds[i] = 0x404040;
                }
                
                redCounter += direc;
                orangeCounter -= direc;
                
                sideRedCounter += direc * sideSpeed;
                sideOrangeCounter -= direc * sideSpeed;
                
                Serial.println(sideRedCounter);
                
                if (redCounter == 23) {
                    direc = 1;
                    sideRedCounter = 0;
                    sideOrangeCounter = 22;
                } else if (redCounter == 39) {
                    direc = -1;
                }
            }
            
            delayCounter++;
            delayCounter %= delayMax; //start at full speed, then go to half
        }
        
        void reset(){
            delayCounter = 0;
            redCounter = 23;
            orangeCounter = 40;
            direc = 1;
            
            for (int i = 0; i < NUM_LEDS; i++){
                if (i == redCounter)         leds[i] = RED;
                else if (i == orangeCounter) leds[i] = ORANGE;
                else                         leds[i] = WHITE;
            }
        }
};

#endif
