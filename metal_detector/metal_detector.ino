int calib_mq4 = 0; 

constexpr int GAS = A1;;
constexpr int METAL = A4;
constexpr int BUZZER = 8;

constexpr int M_DIR1 = 10;
constexpr int M_DIR2 = 12;

enum dir { UP, DOWN };

unsigned long last_time = 0;
unsigned long loop_time = 1000;
enum dir cur_dir = UP;


bool calib_done = false;



void up() {
  Serial.println("up");
  digitalWrite(M_DIR1, HIGH);
  digitalWrite(M_DIR2, LOW);
}

void down() {
  Serial.println("down");
  digitalWrite(M_DIR1, LOW);
  digitalWrite(M_DIR2, HIGH);
}

void setup() {
  pinMode(GAS,INPUT); 
  pinMode(METAL, INPUT);

  pinMode(M_DIR1, OUTPUT);
  pinMode(M_DIR2, OUTPUT);
  Serial.begin(9600);

  unsigned long long calib_sum = 0;
  for (int i = 0; i < 25; i++) {
    analogRead(GAS);
    delay(500);
  }
  Serial.print("Calibrating.");
//  for (int i = 0; i < 25; i++) {
    analogRead(GAS);
//    delay(500);
//  }
  for (int i = 0; i < 10; i++) {
    int val = analogRead(GAS);
    calib_sum += val;
    delay(500);
    Serial.println(val);
  }
  calib_mq4 = calib_sum / 10;
  Serial.println("\nDone!\n");
  Serial.print("Calibrated value: ");
  Serial.println(calib_mq4);



}

int last = -1;
void loop() {

  unsigned long cur_time = millis();
  
  if (cur_time - last_time >= loop_time) {
      cur_dir = (cur_dir == UP) ? DOWN : UP;
      if (cur_dir == UP) up();
      else down();
      last_time = cur_time;
  }
  
  int a = analogRead(METAL);
  a = analogRead( METAL );

  delay(50);

  int gas = analogRead(GAS  );
  gas = analogRead( GAS );

  delay(50);


 Serial.print("gas=");
  Serial.print(gas);
  Serial.println();

//  Serial.print("metal=");
//  Serial.print(a);
//  Serial.println();
  
  if (abs(gas - calib_mq4) >= 50) {
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
//     Serial.println("metal found");
    tone(8, 10000, 1000);
  } 
//  last = a;

//  delay(500);
  
}
