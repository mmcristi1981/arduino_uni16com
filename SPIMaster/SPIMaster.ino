
//MEGA2560

void setup() {
  Serial.begin(9600);
  //1111 0111
  // 3-> MISO IN
  // 2->SCK OUT
  // 1->MOSI OUT
  // 0->SS OUT
  DDRB &= 0xF7; 
  DDRB |= 0x07;
  
  SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1); //|(1<<SPIE)

  //SS to 1
  PORTB |= 0x01;
}

void spi_begin() {
  //write SS out to 0
  PORTB &= 0xFE; //1111 1110
}

void spi_end() {
   PORTB |= 0x01; //1111 1110
}

void spi_send(uint8_t v) {
  SPDR = v;
}

uint8_t spi_done() {
  return (SPSR & 0x80) == 0x80; //1000 0000
}

uint8_t spi_get() {
  return SPDR;
}

uint16_t val = 1;
void loop() {
   spi_begin();
   spi_send((uint8_t)(val >> 8));
   while (!spi_done()) {
   }
   //delayMicroseconds(100);
   spi_send((uint8_t)(val));
   while (!spi_done()) {
   }
   spi_end();
   Serial.print("sent:");
   Serial.print(val);
   Serial.print(" rec:");
   Serial.println(spi_get());
   val +=101;
   delay(300);
}
