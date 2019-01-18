

int DATA_PIN = 4;
int CLK_PIN = 2;

unsigned int delim;
unsigned int data;
unsigned int bitCount;
bool newByte;

volatile unsigned int value;
volatile unsigned int ints = 0;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(DATA_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);

  int interrupt = digitalPinToInterrupt(CLK_PIN);
  attachInterrupt(interrupt, onClock, RISING);
  delim = 0;
}

void onClock() {
  ints ++;
  unsigned int d = (unsigned int)digitalRead(DATA_PIN);
  //Serial.print(d);
  delim = (delim << 1) | d;
  //16x1 bit
  if (delim == 0xFFFF) {
    data = 0;
    bitCount = 0;
    newByte = true;
  } else if (newByte) {
    data = (data << 1) | d;
    //data = data | d;
    bitCount ++;
    if (bitCount == 16) {
      value = data;
      newByte = false;
    }
  }
}

unsigned int prev = 0;

// the loop function runs over and over again forever
void loop() {
  if (prev != value) {
    //Serial.print("value: ");
    Serial.print(" i: ");
    Serial.print(ints);
    Serial.print(" received: ");
    Serial.println(value);
    prev = value;
  }
 
  delay(10);
}
