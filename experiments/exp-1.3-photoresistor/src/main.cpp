#include <Arduino.h>

#define LDR_PIN 34

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Photoresistor (LDR) ===");
}

void loop() {
  int lightRaw = analogRead(LDR_PIN);
  Serial.printf("Light (raw ADC): %d\n", lightRaw);
  Serial.println("---");
  delay(2000);
}
