#include <Arduino.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== DHT11 Humidity/Temperature ===");

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.printf("Temperature: %.2f *C\n", temperature);
    Serial.printf("Humidity:    %.2f %%\n", humidity);
  }
  Serial.println("---");
  delay(2000);
}
