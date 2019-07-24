int ledPin=13;
void setup()
{ Serial.begin(9600);
  

}

void loop() {
  byte input=Serial.read();
  if(input =='a')
    digitalWrite(ledPin,HIGH);
  else if(input =='b')
    digitalWrite(ledPin,LOW);
  

}
