const int p1=6;
const int p2=7;
const int p3=4;
const int p4=5;
const int trig=11;
const int echo=10;
const int t=10;//time for turning
 unsigned long currentmillis;
 unsigned long startmillis;
 unsigned long d;

int dis()//ultrasonic sensor 
{
 digitalWrite(trig,LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  long duration=pulseIn(echo,HIGH);
  
  int dist= (duration*0.034)/2;
  return dist;

}
void rn()//forward
{
  digitalWrite(p1,HIGH);
  digitalWrite(p2,LOW);
  digitalWrite(p3,HIGH);
  digitalWrite(p4,LOW);
  
}
void stp()//stop
{
  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,LOW);
}

void turn()//turn
{
  digitalWrite(p1,HIGH);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,HIGH);
  
}
void setup() {
  //motors setup
  pinMode(p1,OUTPUT);
  pinMode(p2,OUTPUT);
  pinMode(p3,OUTPUT);
  pinMode(p4,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 Serial.begin(9600);

}


void loop() {
  // SERIAL COMMUNICATION
  if(Serial.available())
 {
  char c=Serial.read();
  if(c=='f')
  {
   startmillis=millis(); 
   rn();
   if(dis()<=15)
   {
    currentmillis=millis();
    stp();
    turn();
    delay(2*t);
    stp();
   }
 d=currentmillis-startmillis;
   rn();//use millis here
   delay(d);
   stp();
  }
   else
   if(c=='s')
   stp();//stop
   else if(c=='t')//turn
   {
    turn();
    delay(t);
    stp();
    Serial.write('k');
   }
 }

}
