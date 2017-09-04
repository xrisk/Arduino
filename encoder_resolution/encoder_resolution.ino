int apin = 2;
int bpin = 5;
unsigned long last_rpm_calc = 0;

unsigned long last_count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(apin, INPUT);
  pinMode(bpin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupt, CHANGE);
}

volatile unsigned long count = 0;

void interrupt() {
  count++;
}

void loop() {
 
  unsigned long cur_time = millis();
  unsigned long cnt = count;
  if (cur_time - last_rpm_calc > 200) {
    float rpm = ((cnt - last_count) * (0.0005)) / (float) ((cur_time - last_rpm_calc) * 1e-3);
    rpm *= 60;
    last_count = cnt; last_rpm_calc = cur_time;
    Serial.println("RPM is " + String(rpm)); 
  }

}
   

