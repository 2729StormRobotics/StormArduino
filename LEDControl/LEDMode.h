#ifndef LED_MODE_H
#define LED_MODE_H

#include "commonIncludes.h"

class LEDMode {
    public:
        virtual int  getDelay();
        virtual void doLoop();
        virtual void reset();
};

#endif
