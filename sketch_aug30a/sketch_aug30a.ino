const int led=12;
int Delay=1000;
void setup() {
 pinMode(led,OUTPUT);

}

void loop() {
  Delay=Delay-100;
  if(Delay<=100)
  {
    Delay=1000;
  }

digitalWrite(led,HIGH);
delay(Delay);
digitalWrite(led,0);
delay(Delay);
}
