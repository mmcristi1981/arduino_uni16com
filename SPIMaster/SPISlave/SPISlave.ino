
volatile uint16_t received;
volatile uint8_t rec_flag;
volatile uint8_t rec;

// reception complete ISR
ISR(SPI_STC_vect)
{
  //rec ++;
  rec_flag = 1;
  //received = SPDR;
  received <<= 8;
  received |= (uint16_t)SPDR;
}

void setup() {
  Serial.begin(9600);
  //1111 0111
  // 4->MISO OUTPUT
  // 2->SCK INPUT
  // 1->MOSI INPUT
  // 0->SS INPUT  
  DDRB |= 0x10;     //MISO as OUTPUT, rest as input
  DDRB &= 0xF8;
  
  SPCR = (1<<SPE) | (1<<SPIE);   //Enable SPI
}

void loop() {
  //check SS flag
//  if (rec_flag) {
//    Serial.println("REC");
//    //uint8_t b = PORTB;
//    Serial.println(digitalRead(10));
//  }
  if ( rec_flag && ((PINB & 0x04) == 0x04)) {
    rec_flag = 0;
    Serial.print("rec:");
    Serial.println(received);
    received = 0;
    SPDR = 0xFF;
  }
  delay(1);
  
}
