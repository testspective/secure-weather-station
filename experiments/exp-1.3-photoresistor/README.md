# Experiment description
This experiment reads a photoresistor (LDR) through a voltage divider and previews the raw light level over Serial.

## Photoresistor
[main.cpp](src/main.cpp) reads the divider tap on GPIO34 (ADC1, input-only) and prints the raw
`analogRead()` value (0-4095) every 2 seconds. No lux conversion is done — there's no calibration
curve for this specific LDR, so the raw ADC value is the honest measurement.

### Wiring

Voltage divider, LDR on the high side:

```
3V3 ──[ LDR ]── GPIO34 ──[ 10kΩ ]── GND
```

| Signal | ESP32 |
|---|---|
| LDR leg 1 | 3V3 |
| LDR leg 2 + 10kΩ leg 1 (divider tap) | GPIO34 |
| 10kΩ leg 2 | GND |

This orientation makes brighter light produce a *higher* raw ADC reading. With this LDR (~100Ω in
bright light, ~22kΩ in darkness) and a 10kΩ divider resistor:
- Bright (~100Ω): V ≈ 3.3 × 10k/(10k+100) ≈ 3.27V
- Dark (~22kΩ): V ≈ 3.3 × 10k/(10k+22k) ≈ 1.03V
