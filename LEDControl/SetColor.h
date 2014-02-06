#ifndef SET_COLOR_H
#define SET_COLOR_H

#include "commonIncludes.h"
#include "LEDMode.h"

class SetColor : public LEDMode {
    byte r;
    byte g;
    byte b;

    public:
        SetColor() : r(0), g(0), b(0) {}
        void doLoop(){}
        
        void reset(){
            for (uint8_t i = 0; i < NUM_LEDS; i++){
                leds[i].r = r;
                leds[i].g = g;
                leds[i].b = b;
            }
        }

        void changeColor(byte _r, byte _g, byte _b){
            r = _r;
            g = _g;
            b = _b;
        }
};

#endif
