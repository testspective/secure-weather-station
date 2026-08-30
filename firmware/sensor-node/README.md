# Sensor node (ESP32 #1)

Firmware for Module 1 — the sensor node — from the [project architecture](../../README.md#architecture).
Reads onboard sensors and (eventually) sends readings to the gateway over ESP-NOW.

## Status

- [x] BMP280 — temperature + pressure, over I2C (ported from [experiments/exp-1.1-barometer](../../experiments/exp-1.1-barometer))
- [x] DHT11 — humidity (+ temperature), ported from [experiments/exp-1.2-dht11](../../experiments/exp-1.2-dht11)
- [x] Photoresistor — light intensity, ported from [experiments/exp-1.3-photoresistor](../../experiments/exp-1.3-photoresistor)
- [x] LM35 — analog temperature, 0-100°C range, ported from [experiments/exp-1.4-lm35](../../experiments/exp-1.4-lm35)
- [ ] ESP-NOW sender

## Schematic

A combined KiCad schematic showing all four sensors wired to the ESP32 on one sheet: open [hardware/wiring/sensor-node.kicad_pro](../../hardware/wiring/sensor-node.kicad_pro) in [KiCad](https://kicad.org) (free). It was authored without opening it in KiCad to render/verify, so give it a first-open check before relying on it. The per-sensor tables below remain the quick step-by-step reference and are the source of truth the schematic was built from.

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

## Wiring (Photoresistor)

Voltage divider, LDR on the high side: `3V3 ──[ LDR ]── GPIO34 ──[ 10kΩ ]── GND`

| Signal | ESP32 |
|---|---|
| LDR leg 1 | 3V3 |
| LDR leg 2 + 10kΩ leg 1 (divider tap) | GPIO34 |
| 10kΩ leg 2 | GND |

## Wiring (LM35)

| LM35 pin | ESP32 |
|---|---|
| VCC (flat side, pin 1) | 5V / VIN *(not 3V3 — LM35 needs ≥4V)* |
| GND (pin 3) | GND |
| OUT (pin 2) | GPIO35 |