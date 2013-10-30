//see example code for wiring

#define LEDCount 32 //If the strip doesn't change

long leds[LEDCount];

int SDI = 2; //Red wire (not the red 5V wire!)
int CKI = 3; //Green wire
int ledPin = 13; //On board LED

class LEDMode {
  public:
    virtual void initialize();
    virtual void doLoop();
};

class Idle : public LEDMode {
  int count = 0;

  public:
    void initialize() {
      for (int i = 0; i < LEDCount; i++){
        if (i % 3 == 0) leds[i] = 0xFFFFFF;
        else            leds[i] = 0x000000;
      }
    }
    
    void doLoop(){
      count++;
      count = count % 3;
  
      for (int i = 0; i < LEDCount; i++){
        if ((i + count) % 3 == 0) leds[i] = 0xFFFFFF;
        else                      leds[i] = 0x000000;
      }
    }
};

LEDMode* currentMode = new Idle();

void setup(){
  currentMode->initialize();
}

void loop(){
  currentMode->doLoop();
  post_frame();
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
