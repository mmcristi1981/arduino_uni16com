

int DATA_PIN = 4;
int CLK_PIN = 3;

uint16_t value;

uint8_t masks[8] = {128, 64, 32, 16, 8, 4, 2, 1};
uint8_t delim_count;
 
int8_t state; //0 set data pin, 1 set clock high, 2 set clock low

uint8_t bytes[4];
uint8_t byte_index;
uint8_t bit_index;


void prepare(uint16_t data) {
  bytes[0]=0xFFFF;
  bytes[1]=0xFFFF;
  
  bytes[2] = (uint8_t) (data >> 8);
  bytes[3] = (uint8_t) (data);
  
  byte_index = 0;
  bit_index = 0;
  //count = 16;
  state = 0;
}

uint8_t nextBit() {
  if (byte_index == 4) {
    return 1;
  }
  uint8_t result = (bytes[byte_index] & masks[bit_index]) > 0;
  bit_index ++;
  if (bit_index == 8) {
    bit_index = 0;
    byte_index ++;
  }
  return result;
}


void clk() {
    if (state) {
      uint8_t b = nextBit();
      digitalWrite(DATA_PIN, b);
      digitalWrite(CLK_PIN, 1);
      state = 0;
    } else {
      digitalWrite(CLK_PIN, 0);
      state = 1;
    }
}

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
}

uint16_t val  =1;

// the loop function runs over and over again forever
void loop() {
  if (byte_index == 4) {
    val += 500;
  
    if (val > 32000) {
      val = 0;
    }
    
    value = val ;
    prepare(value);
    //send(val);
    Serial.println();
    Serial.print(" v:");
    Serial.print(val);
    Serial.print(" ");
    delay(100);
  }

  unsigned long s = micros();
 
  for (int i=0; i < 64; i++) {
      clk();
      delayMicroseconds(1);
  }
  unsigned long e = micros();
      
  Serial.println();
  Serial.print("cycle:");
  Serial.println((e-s));
  //send(value);
  delay(1000);
  
}
