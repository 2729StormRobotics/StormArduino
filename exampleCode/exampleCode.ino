/*
  Nathan Seidle
  SparkFun Electronics 2011
  
  This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
  
  Controlling an LED strip with individually controllable RGB LEDs. This stuff is awesome.
  
  The SparkFun (individually controllable) RGB strip contains a bunch of WS2801 ICs. These
  are controlled over a simple data and clock setup. The WS2801 is really cool! Each IC has its
  own internal clock so that it can do all the PWM for that specific LED for you. Each IC
  requires 24 bits of 'greyscale' data. This means you can have 256 levels of red, 256 of blue,
  and 256 levels of green for each RGB LED. REALLY granular.
 
  To control the strip, you clock in data continually. Each IC automatically passes the data onto
  the next IC. Once you pause for more than 500us, each IC 'posts' or begins to output the color data
  you just clocked in. So, clock in (24bits * 32LEDs = ) 768 bits, then pause for 500us. Then
  repeat if you wish to display something new.
  
  This example code will display bright red, green, and blue, then 'trickle' random colors down 
  the LED strip.
  
  You will need to connect 5V/Gnd from the Arduino (USB power seems to be sufficient).
  
  For the data pins, please pay attention to the arrow printed on the strip. You will need to connect to
  the end that is the begining of the arrows (data connection)--->
  
  If you have a 4-pin connection:
  Blue = 5V
  Red = SDI
  Green = CKI
  Black = GND
  
  If you have a split 5-pin connection:
  2-pin Red+Black = 5V/GND
  Green = CKI
  Red = SDI
 */

int SDI = 2; //Red wire (not the red 5V wire!)
int CKI = 3; //Green wire
int ledPin = 13; //On board LED

#define STRIP_LENGTH 32 //32 LEDs on this strip
long strip_colors[STRIP_LENGTH];

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //Clear out the array
  for(int x = 0 ; x < STRIP_LENGTH ; x++)
    strip_colors[x] = 0;
    
  randomSeed(analogRead(0));
  
  //Serial.begin(9600);
  //Serial.println("Hello!");
}

void loop() {
  //Pre-fill the color array with known values
  strip_colors[0] = 0xFF0000; //Bright Red
  strip_colors[1] = 0x00FF00; //Bright Green
  strip_colors[2] = 0x0000FF; //Bright Blue
  strip_colors[3] = 0x010000; //Faint red
  strip_colors[4] = 0x800000; //1/2 red (0x80 = 128 out of 256)
  post_frame(); //Push the current color frame to the strip
  
  delay(2000);

  while(1){ //Do nothing
    addRandom();
    post_frame(); //Push the current color frame to the strip

    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(250);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(250);                  // wait for a second
  }
}

//Throws random colors down the strip array
void addRandom(void) {
  int x;
  
  //First, shuffle all the current colors down one spot on the strip
  for(x = (STRIP_LENGTH - 1) ; x > 0 ; x--)
    strip_colors[x] = strip_colors[x - 1];
    
  //Now form a new RGB color
  long new_color = 0;
  for(x = 0 ; x < 3 ; x++){
    new_color <<= 8;
    new_color |= random(0xFF); //Give me a number from 0 to 0xFF
    //new_color &= 0xFFFFF0; //Force the random number to just the upper brightness levels. It sort of works.
  }
  
  strip_colors[0] = new_color; //Add the new random color to the strip
}

//Takes the current strip color array and pushes it out
void post_frame (void) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    long this_led_color = strip_colors[LED_number]; //24 bits of color data

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
