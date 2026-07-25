#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define SEALEVEL_HPA 1013.25

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== BMP280 Barometer ===");

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
}

void loop() {
  Serial.printf("Temperature: %.2f *C\n", bmp.readTemperature());
  Serial.printf("Pressure:    %.2f hPa\n", bmp.readPressure() / 100.0F);
  Serial.printf("Altitude:    %.2f m\n", bmp.readAltitude(SEALEVEL_HPA));
  Serial.println("---");
  delay(2000);
}
