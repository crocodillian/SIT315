//Set pin numbers
const uint8_t PIR_PIN = 2;
const uint8_t LED_PIN = 13;

//Global variables
volatile uint8_t PIRState = 0;

//Set up the pins
void setup()
{
  //Input pin for the button
  pinMode(PIR_PIN, INPUT);
  //Output pin for LED
  pinMode(LED_PIN, OUTPUT);
  
 //Interrupt Function when button is pressed
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), PIRInterrupt, CHANGE);
}

void loop()
{
  //Simulated delay due to some complicated internal processes
  delay(500);
}

void PIRInterrupt()
{
  //Checks PIR signal and turns on LED when interrupted
  PIRState = digitalRead(PIR_PIN);

  digitalWrite(LED_PIN, PIRState);
}




