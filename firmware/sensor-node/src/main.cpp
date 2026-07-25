#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define SEALEVEL_HPA 1013.25

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define LDR_PIN 34

#define LM35_PIN 35

Adafruit_BMP280 bmp;
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Sensor Node ===");

  Wire.begin(I2C_SDA, I2C_SCL);

  if (!bmp.begin(0x77)) {
    Serial.println("Could not find BMP280 at 0x77 - check wiring or try 0x76 (SDO tied low).");
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                   Adafruit_BMP280::SAMPLING_X2,
                   Adafruit_BMP280::SAMPLING_X16,
                   Adafruit_BMP280::FILTER_X16,
                   Adafruit_BMP280::STANDBY_MS_500);

  dht.begin();
}

void loop() {
  Serial.printf("Temperature (BMP280): %.2f *C\n", bmp.readTemperature());
  Serial.printf("Pressure:              %.2f hPa\n", bmp.readPressure() / 100.0F);
  Serial.printf("Altitude:              %.2f m\n", bmp.readAltitude(SEALEVEL_HPA));

  float dhtTemp = dht.readTemperature();
  float dhtHumidity = dht.readHumidity();
  if (isnan(dhtTemp) || isnan(dhtHumidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.printf("Temperature (DHT11):  %.2f *C\n", dhtTemp);
    Serial.printf("Humidity (DHT11):     %.2f %%\n", dhtHumidity);
  }

  int lightRaw = analogRead(LDR_PIN);
  Serial.printf("Light (raw ADC):       %d\n", lightRaw);

  int lm35Millivolts = analogReadMilliVolts(LM35_PIN);
  Serial.printf("Temperature (LM35):    %.2f *C\n", lm35Millivolts / 10.0F);

  Serial.println("---");
  delay(2000);
}
