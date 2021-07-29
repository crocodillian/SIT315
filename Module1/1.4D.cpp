// C++ code
//we will have an additional seonsor on pin 10 that can trigger an interrupt
//When PIR1 triggers, an "A" note will play
//When PIR2 triggers, a "B" will play
//When the device is tilted, "C#" will play as long as device is tilted

//decaler variables to keep track of sensors
volatile byte pir1, pir2, tilt = 0;
//Timer increments every second
volatile byte seconds = 0;
//Pin setup
const uint8_t PIR_1 = 2;
const uint8_t PIR_2 = 10;
const uint8_t TILT = 3;
const uint8_t PIEZO = 8;
const uint8_t LED = 13;

void setup()
{
  noInterrupts();
  //clear registers for timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 62499;  // = 16000000 / (256 * 1) - 1 
  //Turn on TCC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
 
  //Set up pin modes
  pinMode(LED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(PIR_1, INPUT);
  pinMode(PIR_2, INPUT);
  pinMode(TILT, INPUT);
  //Turn on serial
  Serial.begin(9600);
  
  //Turn on additional interrupts
  PCICR |= 0b00000001;	//Turn on port b
  
  PCMSK0 |= 0b00000100; //Enable pin 10 for interrupt
  
  digitalWrite(TILT, HIGH);
  //attach 2 other interrupts using default interrupt
  attachInterrupt(digitalPinToInterrupt(PIR_1), PIRInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TILT), TiltInterrupt, CHANGE);
  
  interrupts();
}

void loop()
{
  Serial.print("Seconds:");
  Serial.print(seconds);
  Serial.print("  PIR1:");
  Serial.print(pir1);
  Serial.print("  PIR2:");
  Serial.print(pir2);
  Serial.print("  TILT:");
  Serial.print(tilt);
  Serial.println("");
  
  //simulated delay
  delay(500);
}

ISR(PCINT0_vect){
  //Checks which pin is activated
  if (PINB && B00000100)
  {
    pir2 = digitalRead(PIR_2);
  }
  else
  {
    pir2 = LOW;
  }
  //Only plays note on rising edge
  if (pir2 == HIGH)
  {
     tone(PIEZO, 440, 1000);
  }

}

void PIRInterrupt()
{
  pir1 = digitalRead(PIR_1);
  if (pir1 == HIGH)
  {
    //Plays B on rising edge
    tone(PIEZO, 494, 1000);
  }
}

void TiltInterrupt()
{
  tilt = digitalRead(TILT);
  //Plays C# until untilted.
  if (tilt == HIGH)
  {
    tone(PIEZO, 554);
  }
  else
  {
    noTone(PIEZO);
  }

}
//Timer used to flash LED and increments seconds counter
ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED, digitalRead(LED) ^ 1);
  seconds++;
}