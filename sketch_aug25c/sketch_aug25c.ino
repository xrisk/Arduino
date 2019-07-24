int calib_mq4 = 0;

void setup() {
  pinMode(A2,INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);

  unsigned long long calib_sum = 0;
  Serial.print("Calibrating.");
  for (int i = 0; i < 100; i++) {
    calib_sum += analogRead(A4);
    delay(20);
    Serial.print(".");
  }
  calib_mq4 = calib_sum / 100;
  Serial.println("\nDone!\n");
  Serial.print("Calibrated value: ");
  Serial.println(calib_mq4);

}

int last = -1;
void loop() {
  int a = analogRead(A2);
  int gas = analogRead(A4);
  Serial.println(gas);
  
  if (abs(gas - calib_mq4) >= 200) {
    noTone(8);
    Serial.println("gas found");
    tone(8, 40000, 1000);
  }
  
  if (last == -1) {
    last = a;
    return;
  }
  if (abs(a - last) >= 10) {
    noTone(8);
     Serial.println("metal found");
    tone(8, 10000, 1000);
  } 
  last = a;
  
}
