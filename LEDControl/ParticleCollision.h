#ifndef PARTICLE_COLLISION_H
#define PARTICLE_COLLISION_H

#include "commonIncludes.h"
#include "LEDMode.h"

class ParticleCollision : public LEDMode {
    bool exploded;
    bool justExploded;
    double count;
    double vel;
    double accel;
    CRGB currColor;

    public:
        ParticleCollision() : exploded(false), justExploded(false), count(0), vel(0.05), accel(0.1), currColor(YELLOW) {}
        void doLoop(){
            if (!exploded){
                for (int i = 0; i < NUM_LEDS; i++){
                    if (i == (int) count || i == NUM_LEDS - (int) count - 1) leds[i] = WHITE;
                    else                                                     leds[i] = BLACK;
                }
                count += vel;
                vel += accel;
                if (count >= (NUM_LEDS / 2)){
                    count = 0;
                    vel = 0.05;
                    exploded = true;
                    justExploded = true;
                }
            } else {
                if (justExploded){
                    for (int i = 0; i < NUM_LEDS; i++) {
                        leds[i] = BLACK;
                    }
                    justExploded = false;
                }
                leds[NUM_LEDS / 2 - 1] = currColor;
                leds[NUM_LEDS / 2]     = currColor;
                for (int i = 0; i < (NUM_LEDS / 2); i++){
                    leds[i] = leds[i + 1];
                    leds[NUM_LEDS - i - 1] = leds[NUM_LEDS - i - 2];
                }

                int r = currColor.r;
                r -= 20;
                if (r < 0) r = 0;
                currColor.r = r;

                int g = currColor.g;
                g -= 40;
                if (g < 0) g = 0;
                currColor.g = g;

                if (++count == (NUM_LEDS / 2) + (255 / 20) + 5){
                    count = 0;
                    exploded = false;
                    currColor = YELLOW;
                }
            }
        }

        void reset(){
            exploded = false;
            count    = 0;
            currColor = YELLOW;
        }
};

#endif
