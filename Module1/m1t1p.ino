// C++ code
//
int buttonState = 0;
int TMPState = 0;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  TMPState = analogRead(A0);
  Serial.println(TMPState);
  // if tempertaure exceeds 25C, the light will go on.
  if (TMPState >= 153) {
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10);
}
