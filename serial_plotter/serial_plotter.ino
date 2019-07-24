void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


int x = 0;
int y = 0;
void loop() {

  Serial.print(x);
  Serial.write("\t");
  Serial.print(y);
  Serial.println();
  x+=5; y++;
  delay(50);
}
