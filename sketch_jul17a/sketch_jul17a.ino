int n,m;
void setup() {
pinMode(43,OUTPUT);
pinMode(45,OUTPUT);
pinMode(5,OUTPUT);
Serial.begin(9600);

}

void loop() {
if(Serial.available()){
n=Serial.parseInt();
m=Serial.parseInt();
Serial.print(n);
Serial.print(" ");
Serial.println(m);
}
if(n==1){
  digitalWrite(43,HIGH);
  digitalWrite(43,LOW);
  }
if(n==0){
  digitalWrite(43,LOW);
  digitalWrite(43,HIGH);  
}
analogWrite(5,m);
}
