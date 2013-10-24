#define LEDCount 10 //placeholder

class LED {
  public: 
    int r;
    int g;
    int b;

    LED(){
      r = 0;
      g = 0;
      b = 0;
    }

    LED(int _r, int _g, int _b){
      r = _r;
      g = _g;
      b = _b; 
    }

    void setColor(int _r, int _g, int _b){
      r = _r;
      g = _g;
    }
};

LED leds[LEDCount];

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
        if (i % 3 == 0) leds[i].setColor(255, 255, 255);
        else            leds[i].setColor(  0,   0,   0);
      }
    }
    
    void doLoop(){
      count++;
      count = count % 3;
  
      for (int i = 0; i < LEDCount; i++){
        if ((i + count) % 3 == 0) leds[i].setColor(255, 255, 255);
        else                      leds[i].setColor(  0,   0,   0);
      }
    }
};

LEDMode* currentMode = new Idle();

void setup(){
  currentMode->initialize();
}

void loop(){
  currentMode->doLoop();
}

