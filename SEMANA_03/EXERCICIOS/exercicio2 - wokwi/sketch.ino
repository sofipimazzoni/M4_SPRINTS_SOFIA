const int LED1 = 25;
const int LED2 = 33;
const int LED3 = 32;
const int LED4 = 26;
const int LDR = 4;
const int inicial_value = 32;
const int final_value = 4063;
const int button1 = 27;
const int button2 = 21;
int storege_values[100] = {};
int counter = 0;
const int buzzer = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(button1, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation

  int LDR_first_value = analogRead(LDR);
  int LDR_second_value = map(LDR_first_value, inicial_value, final_value, 0, 15);

  int button1_value = digitalRead(button1);
  Serial.println(button1_value);

  if(button1_value == 0){
    storege_values[counter] = LDR_second_value;
    counter += 1;

    digitalWrite(LED1, 1 & LDR_second_value >> 0);
    digitalWrite(LED2, 1 & LDR_second_value >> 1);
    digitalWrite(LED3, 1 & LDR_second_value >> 2);
    digitalWrite(LED4, 1 & LDR_second_value >> 3);

    tone(buzzer, 300 + (100 * LDR_second_value), 1000);
    delay(1000);
  }

  int button2_value = digitalRead(button2);
  if(button2_value == 0){
    for(int i = 0; i < counter; i++){
      digitalWrite(LED1, 1 & storege_values[i] >> 0);
      digitalWrite(LED2, 1 & storege_values[i] >> 1);
      digitalWrite(LED3, 1 & storege_values[i] >> 2);
      digitalWrite(LED4, 1 & storege_values[i] >> 3);

      tone(buzzer, 300 + (100 * storege_values[i]), 1000);
      delay(1000);
    }
  }

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}
