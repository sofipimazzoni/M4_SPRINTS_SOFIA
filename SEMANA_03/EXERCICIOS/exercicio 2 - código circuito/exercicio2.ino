const int LED1 = 7;
const int LED2 = 17;
const int LED3 = 3;
const int LED4 = 10;
const int LDR = 1;
const int inicial_value = 0;
const int final_value = 4063;
const int button1 = 13;
const int button2 = 48;
int storege_values[100] = {};
int counter = 0;
const int buzzer = 37;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
  int LDR_first_value = analogRead(LDR);
  Serial.println(LDR_first_value);

  int LDR_second_value = map(LDR_first_value, inicial_value, final_value, 0, 15);

  Serial.println(LDR_second_value);
  int button1_value = digitalRead(button1);
  Serial.printf("leitura button1 = %i\n",button1_value);

  if(button1_value == 0){
    storege_values[counter] = LDR_second_value;
    counter += 1;

    digitalWrite(LED1, 1 & LDR_second_value >> 0);
    digitalWrite(LED2, 1 & LDR_second_value >> 1);
    digitalWrite(LED3, 1 & LDR_second_value >> 2);
    digitalWrite(LED4, 1 & LDR_second_value >> 3);

    tone(buzzer, 300 + (100 * LDR_second_value), 1000);
    delay(1000);

    button1_value = 1;
  }

  int button2_value = digitalRead(button2);
  Serial.printf("leitura button2 = %i\n",button2_value);

  if(button2_value == 0){
    for(int i = 0; i < counter; i++){
      digitalWrite(LED1, 1 & storege_values[i] >> 0);
      digitalWrite(LED2, 1 & storege_values[i] >> 1);
      digitalWrite(LED3, 1 & storege_values[i] >> 2);
      digitalWrite(LED4, 1 & storege_values[i] >> 3);

      tone(buzzer, 300 + (100 * storege_values[i]), 1000);
      delay(1100);

      button2_value = 1;
    }
  }
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  
  delay(300);
}