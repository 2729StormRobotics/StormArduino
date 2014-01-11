#include <SPI.h>
#include <Ethernet.h>
#include "FastSPI_LED2.h"

#include "commonIncludes.h"
#include "LEDMode.h"
#include "SolidWhite.h"
#include "ColorCycle.h"
#include "Marquee.h"
#include "Pew.h"

enum Mode {
  SOLIDWHITE,
  MARQUEE,
  COLORCYCLE,
  PEW
};

int            port = 1025;
EthernetServer server(port);
byte           mac[] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56};
IPAddress      ip(10,27,29,100);

SolidWhite* solidWhiteInst = new SolidWhite();
ColorCycle* colorCycleInst = new ColorCycle();
Marquee*    marqueeInst    = new Marquee();
Pew*        pewInst        = new Pew();


LEDMode* currentMode = solidWhiteInst;

void setup(){

  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop(){
  currentMode->doLoop();
  FastLED.show();
  changeMode();
  delay(20); //20 ms, or 50 cycles per second
}

void changeMode(){
  EthernetClient client = server.available();
  if (client.connected()){
    while(client.available()){
      byte c = client.read();
      switch (c){
        case SOLIDWHITE:  currentMode = solidWhiteInst;
                                break;
        case COLORCYCLE:  currentMode = colorCycleInst;
                                break;
        case MARQUEE:     currentMode = marqueeInst;
                                break;
        case PEW:         currentMode = pewInst;
                                break;
        default:                break;
      }
    }
    currentMode->reset();
  }
  client.stop();
}
