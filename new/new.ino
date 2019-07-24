const int p1=11;
const int p2=6;
const int p3=12;
const int p4=13;
const int trig=9;
const int echo=8;
const int t=281;//time for turning
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

void turn2()//turn
{
  digitalWrite(p1,LOW);
  digitalWrite(p2,HIGH);
  digitalWrite(p3,HIGH);
  digitalWrite(p4,LOW);
  
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
   while(dis()>15)
   {
    rn();
   }

    currentmillis=millis();
    stp();
    delay(1000);
    scan();
    delay(1000);
    turn();
    delay(t);
    stp();
    delay(1000);
    turn();
    delay(t);
    stp();
    delay(1000);
   
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

void scan() {

  stp();

  int cur_dis = dis();
  int best_so_far = cur_dis;

  // perturb left
  turn();
  delay(10);
  stp();

  cur_dis = dis();
  if (cur_dis < best_so_far) {
    // keep perturbing left till it starts to rise
    best_so_far = cur_dis;
    turn();
    delay(50);
    stp();
    cur_dis = dis();
    if (cur_dis > best_so_far) {
      // restore
      turn2();
      delay(50);
      stp();
      return;
    }
    
  }

  // perturb right 
  turn2();
  delay(50);
  stp();
  turn2();
  delay(50);
  stp();
  
  cur_dis = dis();
  while (cur_dis < best_so_far) {
    // keep perturbing right till it starts to rise

    best_so_far = cur_dis;
    turn2();
    delay(50);
    stp();
    cur_dis = dis();
    if (cur_dis > best_so_far) {
      // restore
      turn();
      delay(50);
      stp();
      return;
    }
  } 

  // perturb back to original position
  turn();
  delay(50);
  stp();
  
}


