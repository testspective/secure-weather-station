# Wiring diagrams

Schematics live here as native [KiCad](https://kicad.org) projects (free, no paid tier). Open `<name>.kicad_pro` in KiCad to view or edit.

## Coverage

- `sensor-node.kicad_pro` / `sensor-node.kicad_sch` — combined schematic for [firmware/sensor-node](../../firmware/sensor-node) (ESP32 #1): BMP280, DHT11, photoresistor (LDR) divider, and LM35 wired together on one sheet. Generated from the pin tables in that firmware's README — the per-sensor markdown tables there remain the quick step-by-step reference; this schematic gives the combined view.

This schematic was authored without opening it in KiCad to render/verify — give it a first-open check before relying on it, and fix up anything (symbol placement, wire routing) that looks off.
