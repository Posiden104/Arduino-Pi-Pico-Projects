enum mode {
  SOLID,
  BLINKING,
  FADE,
  FLAME,
  END
};

mode activeMode = SOLID;
bool switching = false;

int BUTTON_PIN = 14;
int LED_PIN = 15;

// Time interval between brightness steps (in milliseconds)
const int fadeInterval = 10;

// Maximum and minimum brightness values
const int maxBrightness = 255;
const int minBrightness = 0;

// Current brightness value
int brightness = minBrightness;

// Direction flag for fading (true = increasing, false = decreasing)
bool fadingDirection = true;

void turnOn(bool override = false);
void turnOff(bool override = false);
void blink(int ms, bool override = false);
void blink(int on, int off, bool override = false);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
}

void loop1(){
  if(!switching){
    switch(activeMode) {
      case SOLID:
        turnOn();
        break;
      case BLINKING:
        blink(1000);
        break;
      case FADE:
        fade();
        break;
      case FLAME:
        fire();
        break;
    }
  }
}

void fire(){
  if(switching) return;
  analogWrite(LED_PIN, random(120) + 135);
  delay(random(100));
}

void fade() {
  if(switching) return;
  // Update the brightness value based on the fading direction
  if (fadingDirection) {
    for (int i = brightness; i <= maxBrightness; i++) {
      if(switching) return;

      brightness = i;
      // Set the LED brightness
      analogWrite(LED_PIN, brightness);
      
      // Delay for the fade interval
      delay(fadeInterval);
    }
    
    fadingDirection = false;
  } else {
    for (int i = brightness; i >= minBrightness; i--) {
      if(switching) return;

      brightness = i;
      // Set the LED brightness
      analogWrite(LED_PIN, brightness);
      
      // Delay for the fade interval
      delay(fadeInterval);
    }
    
    fadingDirection = true;
  }
}

void loop() {
  bool btn_down = digitalRead(BUTTON_PIN);
  
  if(!switching){
    if(btn_down){
      ack();
      switchModes();
    }
  }

  if(!btn_down & switching){
    switching = false;
  }
  
}

void switchModes(){
  activeMode = static_cast<mode>((activeMode + 1) % (END));
}

void ack(){
  switching = true;
  blink(100, true);
  blink(100, true);
  blink(100, true);
  blink(100, true);
}

void blink(int ms, bool override){
  if(override || !switching) blink(ms, ms, override);
}

void blink(int on, int off, bool override){
  if(override || !switching){
    turnOn(override);
    delay(on);
    turnOff(override);
    delay(off);
  }
}

void turnOn(bool override){
  if(override || !switching){
    digitalWrite(LED_PIN, HIGH);
  }
}

void turnOff(bool override){
  if(override || !switching){
    digitalWrite(LED_PIN, LOW);
  }
}
