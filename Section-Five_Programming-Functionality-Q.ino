const int ledPin = 3;
const int buttonPin = 2;

int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

int mode = 0; 

unsigned long previousMillis = 0;
unsigned long blinkInterval = 1000;  
bool ledOn = true;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  
  digitalWrite(ledPin, HIGH);    
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && buttonState == HIGH) {
      mode = (mode + 1) % 4;
    }
    buttonState = reading;
  }

  lastButtonState = reading;

  switch (mode) {
    case 0:  // On
      digitalWrite(ledPin, LOW);
      break;

    case 1:  // Slow blink
      blinkInterval = 1000;
      blinkLED();
      break;

    case 2:  // Medium blink
      blinkInterval = 500;
      blinkLED();
      break;

    case 3:  // Fast blink
      blinkInterval = 200;
      blinkLED();
      break;
  }
}

void blinkLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledOn = !ledOn;
    digitalWrite(ledPin, ledOn ? HIGH : LOW);
  }
}
