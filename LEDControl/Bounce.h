#ifndef BOUNCE_H
#define BOUNCE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Bounce : public LEDMode {
  
    uint8_t posCounter;
    uint8_t colorCounter;
    uint8_t direc;

    CRGB color1, 
         color2;

    public:
        Bounce() : posCounter(0), colorCounter(0), direc(1), color1(RED), color2(GREEN) {}
        void doLoop() {

            for (uint8_t i = 0; i < NUM_LEDS; i++){
                if      (i == posCounter)                leds[i] = color1;
                else if (i == NUM_LEDS - posCounter - 1) leds[i] = color2;
                else                                     leds[i] = BLACK;
            }
            

            posCounter += direc;

            if (posCounter == 0) {
                direc = 1;
                colorCounter++;
                colorCounter %= 4;

                color1.r = random(256);
                color1.g = random(256);
                color1.b = random(256);

                color2.r = random(256);
                color2.g = random(256);
                color2.b = random(256); 
            }
            else if (posCounter == NUM_LEDS - 1) direc = -1;
        }
        void reset(){
            posCounter     = 0;
            colorCounter = 0;
            direc        = 1;
        }

};

#endif
