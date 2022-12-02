#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>
#include <iostream>
#include <SPI.h>

const int LED_azul_Vx = 39;
const int LED_amarelo_Vo = 36;
const int LED_verde_E = 21;
const int buzzer = 13;

// Change the SSID and PASSWORD here if needed
const char * WIFI_FTM_SSID = "inteli-COLLEGE"; // SSID of AP that has FTM Enabled
const char * WIFI_FTM_PASS = "QazWsx@123"; // STA Password

void httpRequest(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection statu
      HTTPClient http;  //Declare an object of class HTTPClient
      const char* GETCommand = "http://10.128.65.227:5500/winner";

      http.begin(GETCommand);  //Specify request destination
      int httpCode = http.GET(); //Send the request
      Serial.print("Get command: ");
      Serial.println(GETCommand);
      if (httpCode > 0) { //Check the returning code
        String answer = http.getString();   //Get the request response payload
        Serial.println("answer: " + answer);
        Serial.println(answer[6]);                     //Print the response payload
        Serial.println(answer[14]);                     //Print the response payload
                            //Print the response payload
        if (answer[6] == 't'){
          digitalWrite(LED_azul_Vx, HIGH);
          tone(buzzer, 300, 1500);
          delay(1500);
          digitalWrite(LED_azul_Vx, LOW);

        } else if (answer[14] == 't'){
            digitalWrite(LED_amarelo_Vo, HIGH);
            tone(buzzer, 600, 1500);
            delay(1500);
            digitalWrite(LED_amarelo_Vo, LOW);

          } else if (answer[6] == 'e' && answer[14] == 'e'){
              digitalWrite(LED_verde_E, HIGH);
              tone(buzzer, 900, 1500);
              delay(1500);
              digitalWrite(LED_verde_E, LOW); 

            } else {
                Serial.println("No response");
              }

      Serial.println("http code: " + String(httpCode));
      http.end();   //Close connection
    }
  else
  {
    Serial.println("--> connection failed");
  }
  }
}






void setup() {
  Serial.begin(115200);
  Serial.println("Conectando ao Wifi");
  WiFi.begin(WIFI_FTM_SSID, WIFI_FTM_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Conectado");
  delay(500);

  pinMode(LED_azul_Vx, OUTPUT);
  pinMode(LED_amarelo_Vo, OUTPUT);
  pinMode(LED_verde_E, OUTPUT);

}

void loop() {

  httpRequest();
  delay(3000);


}
