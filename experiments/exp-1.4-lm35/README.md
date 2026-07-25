# Experiment description
This experiment reads an LM35 analog temperature sensor and previews the temperature over Serial.

## LM35
[main.cpp](src/main.cpp) reads GPIO35 (ADC1, input-only) via `analogReadMilliVolts()` — which
applies the ESP32's factory ADC calibration — and converts the result to Celsius using the LM35's
datasheet formula (10mV per °C, 0mV = 0°C), printing it every 2 seconds.

Two constraints from the LM35 datasheet:
- **Supply voltage:** the LM35 requires at least 4V, so it's powered from the board's 5V/VIN pin,
  not 3V3.
- **Range:** with a single positive supply and no negative-bias circuit, the LM35 can only output
  0V and up — so it can only represent temperatures from 0°C upward. This experiment (and the
  sensor-node port) accepts a 0-100°C range; BMP280 remains the sensor for real outdoor readings
  including sub-zero temperatures.

### Wiring

| LM35 pin | ESP32 |
|---|---|
| VCC (flat side, pin 1) | 5V / VIN *(not 3V3 — LM35 needs ≥4V)* |
| GND (pin 3) | GND |
| OUT (pin 2) | GPIO35 |
