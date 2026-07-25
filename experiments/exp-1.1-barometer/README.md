# Experiment description
This experiment connects a BMP280 barometer over I2C and previews its readings over Serial.

## Barometer
[main.cpp](src/main.cpp) initializes the BMP280 over I2C (GPIO21 SDA / GPIO22 SCL) and prints
temperature, pressure and estimated altitude every 2 seconds.

### Wiring

| BMP280 | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |