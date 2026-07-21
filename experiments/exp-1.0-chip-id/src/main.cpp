#include <Arduino.h>

#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Who am I? ===");
  Serial.printf("Chip model:  %s\n", ESP.getChipModel());
  Serial.printf("Revision:      %d\n", ESP.getChipRevision());
  Serial.printf("Cores:      %d\n", ESP.getChipCores());
  Serial.printf("CPU Frequency:    %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Flash:        %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("MAC (eFuse):  %012llX\n", ESP.getEfuseMac());
  Serial.printf("SDK:          %s\n", ESP.getSdkVersion());
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

