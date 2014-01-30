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
#include "OneWayPile.h"

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
    PILE,
    ONEWAYPILE
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
OneWayPile*        oneWayPileInst        = new OneWayPile();

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
                Serial.println(c);
                switch (c){
                    case DISABLEDMODE:      {
                                                currentMode = disabledModeInst;
                                                byte alliance = client.read();
                                                disabledModeInst->setAlliance(alliance);
                                                currentMode->reset();
                                                break;
                                            }
                    case COLORCYCLE:        currentMode = colorCycleInst;
                                            currentMode->reset();
                                            break;
                    case MARQUEE:           currentMode = marqueeInst;
                                            currentMode->reset();
                                            break;
                    case PEW:               currentMode = pewInst;
                                            currentMode->reset();
                                            break;
                    case RAINBOWDANCEPARTY: currentMode = rainbowDancePartyInst;
                                            currentMode->reset();
                                            break;
                    case STORMSPIRIT:       currentMode = stormSpiritInst;
                                            currentMode->reset();
                                            break;
                    case BOUNCE:            currentMode = bounceInst;
                                            currentMode->reset();
                                            break;
                    case USA:               currentMode = USAInst;
                                            currentMode->reset();
                                            break;
                    case SETCOLOR:          {
                                                currentMode = setColorInst;
                                                byte r = client.read();
                                                byte g = client.read();
                                                byte b = client.read();
                                                setColorInst->changeColor(r, g, b);
                                                currentMode->reset();
                                                break;
                                            }
                    case PARTICLECOLLISION: currentMode = particleCollisionInst;
                                            currentMode->reset();
                                            break;
                    case PILE:              currentMode = pileInst;
                                            currentMode->reset();
                                            break;
                    case ONEWAYPILE:        currentMode = oneWayPileInst;
                                            currentMode->reset();
                                            break;
                    default:                break;
                }
                
            }
        }
    }
    client.stop();
}
