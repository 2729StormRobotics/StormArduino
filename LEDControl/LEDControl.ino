#include <SPI.h>
#include <Ethernet.h>
#include "FastSPI_LED2.h"

#define NUM_LEDS  32
#define DATA_PIN  11
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

enum Mode {
  SOLIDWHITE,
  MARQUEE,
  COLORCYCLE,
  PEW
};

EthernetClient client;
byte           mac[] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56}; //TODO find mac address
IPAddress      ip(192,168,1,10); //TODO get usable IP Address
IPAddress      robotIP(192,168,1,118); //TODO get robot IP address
int            port = 41900; //TODO get the port

long WHITE   = 0xFFFFFF;
long BLACK   = 0x000000;
long RED     = 0xFF0000;
long GREEN   = 0x00FF00;
long BLUE    = 0x0000FF;
long YELLOW  = 0xFFFF00;
long MAGENTA = 0xFF00FF;
long CYAN    = 0x00FFFF;

class LEDMode {
  public:
    virtual void doLoop();
};

class SolidWhite : public LEDMode {
  public:
    void doLoop() {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
      }
    }
};

class Marquee : public LEDMode {
  int count = 0;

  public:
    void doLoop() {

      for (int i = 0; i < NUM_LEDS; i++){
        if ((i + count) % 3 == 0) leds[i] = WHITE;
        else                      leds[i] = BLACK;
      }

      count++;
      count %= 3;
    }
};

class ColorCycle : public LEDMode {
  int count = 0;
  int delayCounter = 0; //To make it not change every time it cycles, which is 20 times per second

  public:
    void doLoop(){
      if (delayCounter == 0) {
        for (int i = 0; i < NUM_LEDS; i++){
          switch (count){
            case 0:  leds[i] = WHITE;
                     break;
            case 1:  leds[i] = RED;
                     break;
            case 2:  leds[i] = GREEN;
                     break;
            case 3:  leds[i] = BLUE;
                     break;
            case 4:  leds[i] = YELLOW;
                     break;
            case 5:  leds[i] = MAGENTA;
                     break;
            case 6:  leds[i] = CYAN;
                     break;
            default: break;
          }
        }
        count++;
        count %= 7;
      }

      delayCounter++;
      delayCounter %= 20; //Cycle once per second
    }
};

class Pew : public LEDMode {
  int count = 0;
  int colorCounter = 0;

  public:
    void doLoop() {

      long currentColor;

      switch (colorCounter){
        case 0:  currentColor = WHITE;
                 break;
        case 1:  currentColor = RED;
                 break;
        case 2:  currentColor = GREEN;
                 break;
        case 3:  currentColor = BLUE;
                 break;
        default: break;
      }

      for (int i = 0; i < NUM_LEDS; i++){
        if (i == 15 - count || i == 16 + count) leds[i] = currentColor;
        else                                    leds[i] = BLACK;
      }

      count++;
      count %= 15;

      if (count == 0) {
        colorCounter++;
        colorCounter %= 4;
      }
    }

};

SolidWhite* solidWhiteInst = new SolidWhite();
ColorCycle* colorCycleInst = new ColorCycle();
Marquee*    marqueeInst    = new Marquee();
Pew*        pewInst        = new Pew();


LEDMode* currentMode = solidWhiteInst;

void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Serial.println("Starting to look");

  bool connection = false;
  while (!connection){
    if (client.connect(robotIP, port)){
      connection = true;
      Serial.println("Connected!");
    }
    else{
      Serial.println("waiting...");
      delay(1000);
    }
  }

  // Uncomment one of the following lines for your leds arrangement.
  // TODO Find LED strip type
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);

  //This is the chipset in the AM-2640 LED strip
  FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

  FastLED.clear();
}

void loop(){
// Turn the first led red for 1 second
Serial.println("loop");
    leds[0] = CRGB::Red; 
    FastLED.show();
    delay(1000);
    
    // Set the first led back to black for 1 second
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(1000);

  //Serial.println("start loop");
  //currentMode->doLoop();
  //Serial.println("do loop");
  //Serial.println("start post");
  //FastLED.show();
  //Serial.println("done show");
  //delay(1000);
  //Serial.println("done delay");
  //Serial.println("post frame");
  //changeMode();
  //Serial.println("done change mode");
}

void changeMode(){
  Serial.println("change mode!");
  if (client.available()){
    Serial.println("Got a stuff");
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
    Serial.println((int)c);
  }

  //If we lost connection, wait until reconnected
  if (!client.connected()){
    Serial.println("Lost connection. Dammit.");
    bool connection = false;
    while (!connection){
      if (client.connect(robotIP, port)){
        connection = true;
        Serial.println("Connected!");
      }
      else{
        delay(1000);
        Serial.println("waiting...");
      }
    }
  }
}

void post_frame() {
  Serial.println("start post");
  FastLED.show();
  Serial.println("done show");
  delay(1000);
  Serial.println("done delay");
  
}
