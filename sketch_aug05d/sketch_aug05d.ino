
int switch_pin = 5;
int led_pin = 13;

int cur_led_state = LOW;
int last_btn_state = LOW;
int last_reading = LOW;

int lastDebounceEvent = 0;
int debounceInterval = 50;

void setup() {
  Serial.begin(9600);
  pinMode(switch_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  last_btn_state = digitalRead(switch_pin);
}

void loop() {
  int cur_reading =  digitalRead(switch_pin);
  Serial.println(cur_reading);
  int cur_time = millis();
  
  if (cur_reading != last_reading) {
    lastDebounceEvent = cur_time;
    Serial.println("debounce event");
  }

  if ((cur_time - lastDebounceEvent >= debounceInterval)) {
    if (cur_reading == HIGH && last_btn_state == LOW) {
      digitalWrite(led_pin, (cur_led_state = cur_led_state ^= 1));
    }
    last_btn_state = cur_reading;
  }

  last_reading = cur_reading;
}

