#include <Adafruit_INA219.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
const uint8_t pin_ENA = D6;
const uint8_t pin_DIR = D7;
const uint8_t pin_PUL = D8;
Adafruit_INA219 ina219;

uint32_t f = 10000;

const char* ssid = "Azamat";
const char* password = "R00000000";

String getbusvoltage() {
  float busvoltage = 0;
  busvoltage = ina219.getBusVoltage_V();
  return String(busvoltage);
}
String getpower_mW() {
  float power_mW = 0;
  power_mW = ina219.getPower_mW();
  return String(power_mW);
}
String getcurrent_mA() {
  float current_mA = 0;
  current_mA = ina219.getCurrent_mA();
  return String(current_mA);
}




AsyncWebServer server(80);
uint32_t t = 1000000 / f / 2; // Определяем длительность импульсов t3 и пауз t4 в мкс.
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode( pin_ENA, OUTPUT );
  pinMode( pin_DIR, OUTPUT );
  pinMode( pin_PUL, OUTPUT );
  // Initialize the sensor

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  if(!ina219.begin()){
    Serial.println("NO ina219");
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());


  server.on("/right", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 0 ); // Разрешаем работу двигателя.
    delayMicroseconds(5); // Выполняем задержку t1 (см. график STEP/DIR).
    digitalWrite( pin_DIR, 0 ); // Выбираем направление вращения.

    delayMicroseconds(5);
    for (int i = 0; i < 800; i++) { // Выполняем 1600 проходов цикла (1 оборот = 800 тактов, 2 оборота = 1600).
      digitalWrite( pin_PUL, 1 ); // Устанавливаем на выводе PUL состояние логической «1».
      delayMicroseconds(t); // Выполняем задержку t3 (см. график STEP/DIR).
      digitalWrite( pin_PUL, 0 ); // Устанавливаем на выводе PUL состояние логического «0».
      delayMicroseconds(t); // Выполняем задержку t4 (см. график STEP/DIR).
    } //

    request->send_P(200, "text/plain", "right");
  });
  server.on("/left", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 0 ); // Разрешаем работу двигателя.
    delayMicroseconds(5); // Выполняем задержку t1 (см. график STEP/DIR).
    digitalWrite( pin_DIR, 1 ); // Выбираем направление вращения.

    delayMicroseconds(5);
    for (int i = 0; i < 800; i++) { // Выполняем 1600 проходов цикла (1 оборот = 800 тактов, 2 оборота = 1600).
      digitalWrite( pin_PUL, 1 ); // Устанавливаем на выводе PUL состояние логической «1».
      delayMicroseconds(t); // Выполняем задержку t3 (см. график STEP/DIR).
      digitalWrite( pin_PUL, 0 ); // Устанавливаем на выводе PUL состояние логического «0».
      delayMicroseconds(t); // Выполняем задержку t4 (см. график STEP/DIR).
    } //
    request->send_P(200, "text/plain", "left");
  });
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 1 );
    request->send_P(200, "text/plain", "stop");
  });


  server.on("/getbusvoltage", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 1 );
    request->send_P(200, "text/plain", getbusvoltage().c_str());
  });
  server.on("/getpower_mW", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 1 );
    request->send_P(200, "text/plain", getpower_mW().c_str());
  });
  server.on("/getcurrent_mA", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite( pin_ENA, 1 );
    request->send_P(200, "text/plain", getcurrent_mA().c_str());
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
