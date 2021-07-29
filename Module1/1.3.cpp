//Set pin numbers
const uint8_t PIR_PIN = 2;
const uint8_t Tilt_PIN = 3;
const uint8_t LED_1 = 13;
const uint8_t LED_2 = 12;

//Global variables
volatile uint8_t PIRState = 0;
volatile uint8_t LED1State = 0;
volatile uint8_t LED2State = 0;
volatile uint8_t tiltState = 0;
//Set up the pins
void setup()
{
  //Input pins
  pinMode(PIR_PIN, INPUT);
  pinMode(Tilt_PIN, INPUT);
  digitalWrite(Tilt_PIN, HIGH);
  //Output pins
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  //Set up serial for monitoring
  Serial.begin(9600);
  
 //Interrupt Function when button is pressed
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), PIRInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Tilt_PIN), TiltInterrupt, CHANGE);
}

void loop()
{
  Serial.print("PIR:");
  Serial.print(PIRState);
  Serial.print("Tilt:");
  Serial.print(tiltState);
  Serial.println("");
  
  delay(1000);

}

void PIRInterrupt()
{
  //Checks PIR signal and turns on LED 1 when interrupted
  PIRState = digitalRead(PIR_PIN);
  LED1State = PIRState;

  digitalWrite(LED_1, LED1State);
}

void TiltInterrupt()
{
  //Checks whether device is tilted and turns on LED2 if tilted.
  tiltState = digitalRead(Tilt_PIN);
  LED2State = tiltState;

  digitalWrite(LED_2, LED2State);
}
