//see example code for wiring

#define LEDCount 32 //If the strip doesn't change

long leds[LEDCount];

long WHITE   = 0xFFFFFF;
long BLACK   = 0x000000;
long RED     = 0xFF0000;
long GREEN   = 0x00FF00;
long BLUE    = 0x0000FF;
long YELLOW  = 0xFFFF00;
long MAGENTA = 0xFF00FF;
long CYAN    = 0x00FFFF;

int SDI = 2; //Red wire (not the red 5V wire!)
int CKI = 3; //Green wire
int ledPin = 13; //On board LED

class LEDMode {
  public:
    virtual void initialize();
    virtual void doLoop();
};

class Marquee : public LEDMode {
  int count = 0;

  public:
    void initialize() {}
    void doLoop() {
  
      for (int i = 0; i < LEDCount; i++){
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
    void initialize() {}
    void doLoop(){
      if (delayCounter == 0) {
        for (int i = 0; i < LEDCount; i++){
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
    void initialize() {}
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

      for (int i = 0; i < LEDCount; i++){
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

LEDMode* currentMode = new Marquee();

void setup(){
  currentMode->initialize();
}

void loop(){
  currentMode->doLoop();
  post_frame();

  //TODO changing modes
}

//Takes the current strip color array and pushes it out
void post_frame (void) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int LED_number = 0 ; LED_number < LEDCount ; LED_number++) {
    long this_led_color = leds[LED_number]; //24 bits of color data

    for(byte color_bit = 23 ; color_bit != 255 ; color_bit--) {
      //Feed color bit 23 first (red data MSB)
      
      digitalWrite(CKI, LOW); //Only change data when clock is low
      
      long mask = 1L << color_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
      
      if(this_led_color & mask) 
        digitalWrite(SDI, HIGH);
      else
        digitalWrite(SDI, LOW);
  
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}
