#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
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



String getAccelerationX() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float acceleration_x = a.acceleration.x;

  //Serial.println(acceleration_x);
  return String(acceleration_x);
}
String getAccelerationY() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float acceleration_y = a.acceleration.y;

  //Serial.println(acceleration_y);
  return String(acceleration_y);
}

String getAccelerationZ() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float acceleration_z = a.acceleration.z;

  //Serial.println(acceleration_z);
  return String(acceleration_z);
}




String getRotationX() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyro_x = g.gyro.x;

  //Serial.println(acceleration_x);
  return String(gyro_x);
}

String getRotationY() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyro_y = g.gyro.x;

  //Serial.println(acceleration_x);
  return String(gyro_y);
}



String getRotationZ() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyro_z = g.gyro.z;

  //Serial.println(acceleration_x);
  return String(gyro_z);
}









AsyncWebServer server(80);

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
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  //Parameters
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getHumidity().c_str());
  });

  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getPressure().c_str());
  });
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getTemperature().c_str());
  });

  //Acceleration
  server.on("/acceleration_x", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getAccelerationX().c_str());
  });
  server.on("/acceleration_y", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getAccelerationY().c_str());
  });

  server.on("/acceleration_z", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getAccelerationZ().c_str());
  });

  //Rotation
  server.on("/rotation_x", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getRotationX().c_str());
  });
  server.on("/rotation_y", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getRotationY().c_str());
  });

  server.on("/rotation_z", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getRotationZ().c_str());
  });
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
