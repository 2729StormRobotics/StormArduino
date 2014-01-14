#include <SPI.h>
#include <Ethernet.h>
#include "FastSPI_LED2.h"

#include "commonIncludes.h"
#include "LEDMode.h"
#include "SolidWhite.h"
#include "ColorCycle.h"
#include "Marquee.h"
#include "Pew.h"
#include "RainbowDanceParty.h"
#include "StormSpirit.h"

enum Mode {
  SOLIDWHITE,
  MARQUEE,
  COLORCYCLE,
  PEW,
  RAINBOWDANCEPARTY,
  STORMSPIRIT
};

int            port = 1025;
EthernetServer server(port);
byte           mac[] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56};
IPAddress      ip(10,27,29,100);
unsigned long  lastTime;

SolidWhite*        solidWhiteInst        = new SolidWhite();
ColorCycle*        colorCycleInst        = new ColorCycle();
Marquee*           marqueeInst           = new Marquee();
Pew*               pewInst               = new Pew();
RainbowDanceParty* rainbowDancePartyInst = new RainbowDanceParty();
StormSpirit*       stormSpiritInst       = new StormSpirit();


LEDMode* currentMode = solidWhiteInst;

void setup(){

  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println(Ethernet.localIP());
}

void loop(){
  lastTime = millis();
  currentMode->doLoop();
  FastLED.show();
  changeMode();
  delay(20 - (millis() - lastTime)); //20 ms, or 50 cycles per second
  Serial.println(millis() - lastTime);
}

void changeMode(){
  EthernetClient client = server.available();
  if (client.connected()){
    while(client.available()){
      byte c = client.read();
      switch (c){
        case SOLIDWHITE:        currentMode = solidWhiteInst;
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
        default:                break;
      }
    }
    currentMode->reset();
  }
  client.stop();
}
