#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;


const char* ssid = "Bashtel 46";
const char* password = "R00000000";
String getTemperature() {
  float temperature = bme.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float temperature = 1.8 * bme.readTemperature() + 32;
  Serial.println(temperature);
  return String(temperature);
}

String getHumidity() {
  float humidity = bme.readHumidity();
  Serial.println(humidity);
  return String(humidity);
}

String getPressure() {
  float pressure = bme.readPressure() / 100.0F;
  Serial.println(pressure);
  return String(pressure);
}

AsyncWebServer server(5050);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the sensor
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

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


  server.on("/on_led", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(LED_BUILTIN,HIGH);
    request->send_P(200, "text/plain", "on");
  });
  server.on("/off_led", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(LED_BUILTIN,LOW);
    request->send_P(200, "text/plain", "off");
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getTemperature().c_str());
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getHumidity().c_str());
  });

  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getPressure().c_str());
  });
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
