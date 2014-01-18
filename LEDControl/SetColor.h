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
            beds[i].b = b;
        }
    }
    void reset(){
        EthernetClient client = server.available();
        if (client){
            while(client.connected()){
                r = client.read();
                g = client.read();
                b = client.read();
            }
            client.stop();       
        }    
    }

};

#endif
