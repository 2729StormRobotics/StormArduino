#ifndef LED_MODE_H
#define LED_MODE_H

#include "commonIncludes.h"

class LEDMode {
    public:
        virtual void doLoop();
        virtual void reset();
};

#endif
