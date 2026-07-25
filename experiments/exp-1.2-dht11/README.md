# Experiment description
This experiment connects a DHT11 humidity/temperature sensor over a single digital pin and previews its readings over Serial.

## DHT11
[main.cpp](src/main.cpp) initializes the DHT11 on GPIO4 and prints temperature and humidity every 2 seconds.

### Wiring

| DHT11 | ESP32 |
|---|---|
| VCC | 3V3 |
| DATA | GPIO4 *(bridge a 4.7kΩ resistor between VCC and DATA — pull-up required for a bare sensor)* |
| NC | not connected |
| GND | GND |
