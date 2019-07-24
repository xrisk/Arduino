int p1=6;
int p2=7;
void setup() {
  pinMode(p1,OUTPUT);
  pinMode(p2,OUTPUT);
 Serial.begin(9600);
}

void rn()
{
  digitalWrite(p1,HIGH);
  digitalWrite(p2,HIGH);
  
}
void stp()
{
  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
}

void loop() {
 if(Serial.available())
 {
  char c=Serial.read();
  if(c=='f')
   rn();
   else
   if(c=='s')
   stp();
 }

}
