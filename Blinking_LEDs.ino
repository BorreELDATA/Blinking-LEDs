int greenLedPin = 7;
int greenLedState = LOW;

int redLedPin = 8;
int redLedState = LOW;
int redLedBlinkLimit = 19;

int breakDuration = 8000;
int intervalRedLed = 1000;
int intervalGreenLed = 500;

unsigned long currentTime;
unsigned long previousTimeRedLed;
unsigned long previousTimeGreenLed;

int redLedCounter;
boolean redLedIsPaused = false;

boolean redLedIsOn() {
  return digitalRead(redLedPin) == HIGH;
}

void changeGreenLedState() {
  if (greenLedState == HIGH) {
    greenLedState = LOW;
  } else {
    greenLedState = HIGH;
  }
  digitalWrite(greenLedPin, greenLedState);
}

void changeRedLedState() {
  if (redLedIsOn()) {
    redLedState = LOW;
  } else {
    redLedState = HIGH;
  }
  digitalWrite(redLedPin, redLedState);
}

void setup() {
  Serial.begin(9600);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop() {
  currentTime = millis();

  if (redLedIsPaused && currentTime - previousTimeRedLed > breakDuration) {
    Serial.println("Break is over.");
    redLedIsPaused = false;
  }
  
  if (!redLedIsPaused) {
    if (redLedCounter <= redLedBlinkLimit) {
      if (currentTime - previousTimeRedLed > intervalRedLed) {
        Serial.println("redLedCounter: " + (String) redLedCounter);
        previousTimeRedLed = currentTime;
        changeRedLedState();
        if (redLedIsOn()) {
          redLedCounter++;
        }
      }
    }

    // When the red led counter exceeds 19.
    else {
      redLedIsPaused = true;
      redLedCounter = 0;
      changeRedLedState();
      Serial.println("Break has begun.");
    }
  }

  if (currentTime - previousTimeGreenLed > intervalGreenLed) {
    previousTimeGreenLed = currentTime;
    changeGreenLedState();
  }
}
