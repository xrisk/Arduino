void setup() {
  Serial.begin(9600);
}

char turn = 0;

String s;

char me = 'x';
char other = 'y';

void loop() {

  while (Serial.available() > 0) 
  {
    s = Serial.readStringUntil('\n');
    
    if (s[0] == me) // echoed from other arduino
      return;
  
    if (s[0] == other) // sent from other arduino
     {
      Serial.println(s);
      return;
     }
   
    if (!((s[0] == me) || (s[0] == other))) { // from user
      s[0] = me;
      Serial.println(s);
      
    }
  }
  
}

