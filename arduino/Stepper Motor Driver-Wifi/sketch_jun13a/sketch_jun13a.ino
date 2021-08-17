#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
const uint8_t pin_ENA = D0;
const uint8_t pin_DIR = D1;
const uint8_t pin_PUL = D2;

uint32_t f = 10000;

const char* ssid = "Azamat";
const char* password = "R00000000";


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

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
