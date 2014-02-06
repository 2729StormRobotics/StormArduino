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
#include "Collapse.h"

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
    ONEWAYPILE,
    COLLAPSE
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
Collapse*          collapseInst          = new Collapse();

LEDMode* currentMode     = disabledModeInst;
byte     currentModeByte = 0;

void setup(){

    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    Serial.begin(9600);
    Ethernet.begin(mac, ip);
    server.begin();
    currentMode->reset();
}

void loop(){
    lastTime = millis();
    currentMode->doLoop();  
    FastLED.show();
    changeMode();
    
    int time = 20 - (millis() - lastTime);
    if (time < 0) time = 0;
    delay(time); //20 ms, or 50 cycles per second. Usually
    
}

void changeMode(){
    EthernetClient client = server.available();
    
    if (client){
        byte finalMode = 0xFF;
        Serial.println("Got connection");
        while(client.available()){
            byte c = client.read();
            if (c != 0xFF) {//Sure it limits the modes, but let's be honest, it won't
                changeMode(c, &client); 
                Serial.print("Mode is now ");
                Serial.println(c);
                finalMode = c;
            }
        }
    
        Serial.print("Final mode is ");
        Serial.println(finalMode);
        if (finalMode != 0xFF) {
            client.write(finalMode);
            Serial.print("Wrote ");
            Serial.println(finalMode);
        }
        client.stop();
    }
    
}

void changeMode(byte mode, EthernetClient* client){
    switch (mode){
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
        case SETCOLOR:          currentMode = setColorInst;
                                break;
        case PARTICLECOLLISION: currentMode = particleCollisionInst;
                                break;
        case PILE:              currentMode = pileInst;
                                break;
        case ONEWAYPILE:        currentMode = oneWayPileInst;
                                break;
        case COLLAPSE:          currentMode = collapseInst;
                                break;
        default:                return;
    }
    currentMode->reset();
    
    if (mode == DISABLEDMODE){
        byte alliance = client->read();
        disabledModeInst->setAlliance(alliance);
    } else if (mode == SETCOLOR) {
        byte r = client->read();
        byte g = client->read();
        byte b = client->read();
        setColorInst->changeColor(r, g, b);
    }  
}
