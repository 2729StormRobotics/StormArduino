#include <SPI.h>
#include <Ethernet.h>
#include "FastSPI_LED2.h"

#include "commonIncludes.h"
#include "LEDMode.h"
#include "DisabledMode.h"
#include "ColorCycle.h"
#include "Marquee.h"
#include "Pew.h"
#include "RainbowDanceParty.h"
#include "StormSpirit.h"
#include "Bounce.h"
#include "USA.h"
#include "SetColor.h"
#include "ParticleCollision.h"
#include "Pile.h"

enum Mode {
    DISABLEDMODE,
    MARQUEE,
    COLORCYCLE,
    PEW,
    RAINBOWDANCEPARTY,
    STORMSPIRIT,
    BOUNCE,
    USA,
    SETCOLOR,
    PARTICLECOLLISION,
    PILE
};

int            port = 1025;
EthernetServer server(port);
byte           mac[] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56};
IPAddress      ip(10,27,29,100);
unsigned long  lastTime;

DisabledMode*      disabledModeInst      = new DisabledMode();
ColorCycle*        colorCycleInst        = new ColorCycle();
Marquee*           marqueeInst           = new Marquee();
Pew*               pewInst               = new Pew();
RainbowDanceParty* rainbowDancePartyInst = new RainbowDanceParty();
StormSpirit*       stormSpiritInst       = new StormSpirit();
Bounce*            bounceInst            = new Bounce();
USAMode*           USAInst               = new USAMode();
SetColor*          setColorInst          = new SetColor();
ParticleCollision* particleCollisionInst = new ParticleCollision();
Pile*              pileInst              = new Pile();

LEDMode* currentMode = disabledModeInst;

void setup(){

    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    Serial.begin(9600);
    Ethernet.begin(mac, ip);
    server.begin();
}

void loop(){
    lastTime = millis();
    currentMode->doLoop();
    FastLED.show();
    changeMode();
    delay(20 - (millis() - lastTime)); //20 ms, or 50 cycles per second
}

void changeMode(){
    EthernetClient client = server.available();
    if (client){
        while(client.connected()){
            while(client.available()){
                byte c = client.read();
                switch (c){
                    case DISABLEDMODE:      currentMode = disabledModeInst;
                                            break;
                    case COLORCYCLE:        currentMode = colorCycleInst;
                                            break;
                    case MARQUEE:           currentMode = marqueeInst;
                                            break;
                    case PEW:               currentMode = pewInst;
                                            break;
                    case RAINBOWDANCEPARTY: currentMode = rainbowDancePartyInst;
                                            break;
                    case STORMSPIRIT:       currentMode = stormSpiritInst;
                                            break;
                    case BOUNCE:            currentMode = bounceInst;
                                            break;
                    case USA:               currentMode = USAInst;
                                            break;
                    case SETCOLOR:          {
                                                currentMode = setColorInst;
                                                byte r = client.read();
                                                byte g = client.read();
                                                byte b = client.read();
                                                setColorInst->changeColor(r, g, b);
                                                break;
                                            }
                    case PARTICLECOLLISION: currentMode = particleCollisionInst;
                                            break;
                    case PILE:              currentMode = pileInst;
                                            break;
                    default:                break;
                }
                currentMode->reset();
            }
        }
    }
    client.stop();
}
