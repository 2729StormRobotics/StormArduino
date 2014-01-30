#ifndef BOUNCE_H
#define BOUNCE_H

#include "commonIncludes.h"
#include "LEDMode.h"

class Bounce : public LEDMode {
    uint8_t count;
    uint8_t colorCounter;
    uint8_t direc;

    CRGB color1, 
         color2;

    public:
        Bounce() : count(0), colorCounter(0), direc(1), color1(RED), color2(GREEN) {}
        void doLoop() {

            for (uint8_t  i = 0; i < NUM_LEDS; i++){
                if      (i == count)                leds[i] = color1;
                else if (i == NUM_LEDS - count - 1) leds[i] = color2;
                else                                leds[i] = BLACK;
            }
            

            count += direc;

            if (count == 0) {
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
            else if (count == NUM_LEDS - 1) direc = -1;
        }
        void reset(){
            count        = 0;
            colorCounter = 0;
            direc        = 1;
        }

};

#endif
