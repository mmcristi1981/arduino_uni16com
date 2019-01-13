

int DATA_PIN = 4;
int CLK_PIN = 3;

//unsigned int delim;
//unsigned int data;
//unsigned int bitCount;

//unsigned int value;
unsigned int value;


void setup() {
  
  Serial.begin(9600);
//  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
//
//  int interrupt = digitalPinToInterrupt(CLK_PIN);
//  attachInterrupt(interrupt, onClock, RISING);
//  delim = 0;
}

//void onClock() {
//  int d = digitalRead(DATA_PIN);
//  delim = delim << 1;
//  delim |= d;
//  //16x1 bit
//  if (delim == 0xFFFF) {
//    data = 0;
//    bitCount = 0;
//  } else {
//    data = data << 1;
//    bitCount ++;
//    if (bitCount == 16) {
//      value = data;
//    }
//  }
//}

void send(unsigned int v) {
  send16(0xFFFF);
  send16(v);
}

void send16(unsigned int v) {
   int bitCount = 16;
   while (bitCount > 0) {
      unsigned int d = v & 0x0001;
      v = v >> 1;    
      bitCount --;
      // one data bit
      digitalWrite(DATA_PIN, d);
      // one clock cycle
      digitalWrite(CLK_PIN, 1);
      delayMicroseconds(200);
      digitalWrite(CLK_PIN, 0);
      delayMicroseconds(200);
   }
   
}

// the loop function runs over and over again forever
void loop() {
  
  value += 500;
  if (value > 32000) {
    value = 0;
  }
  send(value);
  Serial.print("v:");
  Serial.println(value);
  delay(1000);
  
}
