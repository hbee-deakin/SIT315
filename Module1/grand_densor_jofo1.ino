// sensor pins
const uint8_t pir_pin = PD3;
const uint8_t switch_Pin = PD2;
const uint8_t pir_pin2 = PD5;
const uint8_t switch_Pin2 = PD4;

// timer green led pin
const uint8_t led_green_pin = PB5;

// led pins
const uint8_t led_red_pin = PB3;
const uint8_t led_blue_pin = PB2;
const uint8_t led_orange_pin = PB1;
const uint8_t led_yellow_pin = PB0;

const uint16_t tl_load = 0;
const uint16_t tl_comp = 62500;
  
void setup()
{
  DDRB = B00101111;
  PORTD = B00111100;
  
  PCICR = 0b00000101;  
  PCMSK2 = 0b00111100;  
  
  Serial.begin(9600);
  
  startTimer();
}

void loop()
{ 
  // one second delay for testing interrupt
  delay(1000);
}

ISR(PCINT2_vect) {  
  
  // if pin 5, toggle red led
  if (PIND & B00100000) {
    Serial.println("pin 5, toggle red led ");
   
    PORTB ^= (1 << led_red_pin);
  }
  
  // if pin 4, toggle blue led
  if (PIND & B00010000) {
    Serial.println("pin 4, toggle blue led ");
    PORTB ^= (1 << led_blue_pin);
  }
  
  // if pin 3, toggle orange led
  if (PIND & B00001000) {
    Serial.println("pin 3, toggle orange led ");
    PORTB ^= (1 << led_orange_pin);
  }
  
  // if pin 5, toggle yellow led
  if (PIND & B00000100) {
    Serial.println("pin 5, toggle yellow led ");
    PORTB ^= (1 << led_yellow_pin);
  }
}

void startTimer(){
  
  noInterrupts();
  
  TCCR1A = 0;
  
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

  
  // set prescaler of 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  TCNT1 = tl_load;
  OCR1A = tl_comp;
  
  TIMSK1 = (1 << OCIE1A);
  
  interrupts();
}

// set incrementor for timer print to monitor
int i = 1;

// toggle green led every timer cycle (62500)
ISR(TIMER1_COMPA_vect){
  Serial.print("timer cycle: ");
  Serial.println(i);
  i++;
  
  PORTB ^= (1 << led_green_pin);
}
