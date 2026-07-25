# Sensor node (ESP32 #1)

Firmware for Module 1 — the sensor node — from the [project architecture](../../README.md#architecture).
Reads onboard sensors and (eventually) sends readings to the gateway over ESP-NOW.

## Status

- [x] BMP280 — temperature + pressure, over I2C (ported from [experiments/exp-1.1-barometer](../../experiments/exp-1.1-barometer))
- [x] DHT11 — humidity (+ temperature), ported from [experiments/exp-1.2-dht11](../../experiments/exp-1.2-dht11)
- [ ] Photoresistor — light intensity
- [ ] LM35 — analog temperature (optional)
- [ ] ESP-NOW sender

## Wiring (BMP280)

| BMP280 | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |

## Wiring (DHT11)

| DHT11 | ESP32 |
|---|---|
| VCC | 3V3 |
| DATA | GPIO4 *(bridge a 4.7kΩ resistor between VCC and DATA — pull-up required for a bare sensor)* |
| NC | not connected |
| GND | GND |