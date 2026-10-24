#include <Arduino.h>

#define LED_FAST_PIN 2  // GPIO2 - toggles every FAST_INTERVAL_MS
#define LED_SLOW_PIN 4  // GPIO4 - toggles every SLOW_INTERVAL_MS (2x slower)

const unsigned long FAST_INTERVAL_MS = 250;
const unsigned long SLOW_INTERVAL_MS = 500;

unsigned long lastFastToggle = 0;
unsigned long lastSlowToggle = 0;
bool fastState = LOW;
bool slowState = LOW;

void setup() {
  pinMode(LED_FAST_PIN, OUTPUT);
  pinMode(LED_SLOW_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Who am I? ===");
  Serial.printf("%-16s%s\n", "Chip model:", ESP.getChipModel());
  Serial.printf("%-16s%d\n", "Revision:", ESP.getChipRevision());
  Serial.printf("%-16s%d\n", "Cores:", ESP.getChipCores());
  Serial.printf("%-16s%d MHz\n", "CPU Frequency:", ESP.getCpuFreqMHz());
  Serial.printf("%-16s%d MB\n", "Flash:", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("%-16s%012llX\n", "MAC (eFuse):", ESP.getEfuseMac());
  Serial.printf("%-16s%s\n", "SDK:", ESP.getSdkVersion());
}

void loop() {
  unsigned long now = millis();

  if (now - lastFastToggle >= FAST_INTERVAL_MS) {
    lastFastToggle = now;
    fastState = !fastState;
    digitalWrite(LED_FAST_PIN, fastState);
  }

  if (now - lastSlowToggle >= SLOW_INTERVAL_MS) {
    lastSlowToggle = now;
    slowState = !slowState;
    digitalWrite(LED_SLOW_PIN, slowState);
  }
}

