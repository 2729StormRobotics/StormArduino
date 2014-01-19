#ifndef SET_COLOR_H
#define SET_COLOR_H

#include "commonIncludes.h"
#include "LEDMode.h"

class SetColor : public LEDMode {
    byte r = 0;
    byte g = 0;
    byte b = 0;

    void doLoop(){
        for (int i = 0; i < NUM_LEDS; i++){
            leds[i].r = r;
            leds[i].g = g;
            leds[i].b = b;
        }
    }
    void reset(){}

    public:
    void changeColor(byte _r, byte _g, byte _b){
        r = _r;
        g = _g;
        b = _b;
    }
};

#endif
