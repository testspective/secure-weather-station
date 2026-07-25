#include <Arduino.h>

#define LM35_PIN 35

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== LM35 Analog Temperature ===");
}

void loop() {
  int millivolts = analogReadMilliVolts(LM35_PIN);
  float temperature = millivolts / 10.0F;

  Serial.printf("Temperature (LM35): %.2f *C\n", temperature);
  Serial.println("---");
  delay(2000);
}
