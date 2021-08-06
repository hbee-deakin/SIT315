// sensor pins
const uint8_t pir_pin = 3;
const uint8_t switch_Pin = 2;

// led pins
const uint8_t led_red_pin = 5;
const uint8_t led_blue_pin = 4;

void setup()
{
  DDRD &= ~(1 << pir_pin);
  PORTD |= (1 << pir_pin);
  
  DDRD &= ~(1 << switch_Pin);
  PORTD |= (1 << switch_Pin);
  
  DDRD |= (1 << led_red_pin);
  DDRD |= (1 << led_blue_pin);

  // interrupts for pins 2 and 3 on change
  attachInterrupt(digitalPinToInterrupt(pir_pin), toggleRed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switch_Pin), toggleBlue, CHANGE); 

  Serial.begin(9600);
}

void loop()
{ 
  Serial.print("PIR: ");
  Serial.println(digitalRead(pir_pin));
  
  Serial.print("Switch: ");
  Serial.println(digitalRead(switch_Pin));
  
  // one second delay for testing interrupt
  delay(1000);
}

// toggle red led
void toggleRed() {
  PORTD ^= (1 << led_red_pin);
}

// toggle blue led
void toggleBlue() {
  PORTD ^= (1 << led_blue_pin);
}