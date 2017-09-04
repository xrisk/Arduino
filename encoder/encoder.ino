int apin = 2;
int bpin = 5;
unsigned long last_time = 0;
int last_count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(apin, INPUT);
  pinMode(bpin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);
  Serial.println("Test");
}

volatile unsigned long count = 0;

void interrupt() {
  count++;
}

void loop() {
   unsigned long cur_time = millis();
   if (cur_time - last_time > 500) {
     double revs = (count - last_count) * 0.005;
     last_time = cur_time; last_count = count;
     Serial.print("RPM = ");
     Serial.println(revs / (60.0));
     Serial.println("REVS = " + String(revs));
   }
}
   

