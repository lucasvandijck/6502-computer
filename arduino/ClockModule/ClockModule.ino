const int potPin = A0;  // Analog input pin that the potentiometer is attached to
const int clkPin = A1;

int potVal = 0;  // value read from the pot
long sleepTime = 0; // in microseconds (half period time)

bool pinOn = false;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(clkPin, OUTPUT);
}

void loop() {
  // read the analog in value:
  potVal = analogRead(potPin);

  sleepTime = map(potVal, 0, 1023, 2, 1000);
  sleepTime = sleepTime / 2;

  digitalWrite(clkPin, pinOn);
  pinOn = !pinOn;

  delay(sleepTime);
}
