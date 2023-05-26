const char ADDR[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const char DATA[] = {39, 41, 43, 45, 47, 49, 51, 53};
#define READ_WRITE 3
#define potPin A0
#define clkPin A1

int potVal = 0;  // value read from the pot
long sleepTime = 0; // in microseconds (half period time)
bool pinOn = false;

void setup() {
  for (int n = 0; n < 16; n += 1) {
    pinMode(ADDR[n], INPUT);
  }
  for (int n = 0; n < 8; n += 1) {
    pinMode(DATA[n], INPUT);
  }
  pinMode(clkPin, OUTPUT);
  pinMode(READ_WRITE, INPUT);
  
  Serial.begin(57600);
}

void printData() {
  char output[15];

  unsigned int address = 0;
  for (int n = 0; n < 16; n += 1) {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }
  
  Serial.print("   ");
  
  unsigned int data = 0;
  for (int n = 0; n < 8; n += 1) {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  sprintf(output, "   %04x  %c %02x", address, digitalRead(READ_WRITE) ? 'r' : 'W', data);
  Serial.println(output);  
}

void loop() {
  // read the analog in value:
  potVal = analogRead(potPin);

  sleepTime = map(potVal, 0, 1023, 2, 1000);
  sleepTime = sleepTime / 2;

  digitalWrite(clkPin, pinOn);
  pinOn = !pinOn;

  if (pinOn)
  {
    printData();
  }

  delay(sleepTime);
}
