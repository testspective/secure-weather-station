# 🌦 IoT Weather Station — a Security Testing Playground

<p align="center">
  <a href="#">
    <img src="https://img.shields.io/badge/status-early--stage%20(WIP)-orange">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/focus-IoT%20security-blue">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/hardware-ESP32%20%7C%20Arduino-green">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/license-MIT-lightgrey">
  </a>
</p>

A hands-on weather station built to learn IoT security from the hardware up. The point isn't the weather — it's building a small but *realistic* IoT system (**sensor node → gateway → cloud**) that can later be attacked and hardened, layer by layer.

This repository is part of a *learn-in-public* journey documented on [**Testspective**](https://testspective.com/) — notes and experiments from a QA engineer who expanding his experience towards IoT security. It is a **learning project**, not a production system or a reference design. Expect rough edges, questions left open, and decisions revisited as I learn more.


## The idea

I'm building a weather station, but the weather data is just the excuse. What I actually want is a physical IoT system I fully own and understand, so I can:

1. **Build it** — get real hardware working end to end (sensors → radio → broker → display).
2. **Connect it** — add the IoT/network layer the way real devices do it.
3. **Attack it** — map and probe its attack surface *on my own hardware*, without touching anyone else's systems.

The guiding principle is **layer by layer**: get working hardware first, add connectivity second, add security analysis third. Every build step is meant to carry at least one security observation, so the project keeps its security lens from the very beginning rather than bolting it on at the end.

### Why a weather station?

Because its natural shape mirrors how a huge class of real IoT products is built:

- a **sensor node** out in the field, cheap and battery-minded,
- talking to a **gateway** that concentrates data and bridges it to IP,
- which forwards everything to a **backend / "cloud."**

That's the same node → gateway → cloud pattern you find in smart-home hubs (e.g. a Zigbee bulb → bridge → cloud) and in fleet-telematics gateways. The gateway is the point where everything concentrates — which also makes it the most interesting thing to attack. Recreating that pattern gives a realistic attack surface to learn on, safely and legally.

## Architecture

```
        ┌──────────────────────┐
        │   Module 1 — NODE     │
        │   ESP32 #1            │
        │                       │
        │  BMP280  (temp/press) │
        │  DHT11   (humidity)   │
        │  Photoresistor (light)│
        │  LM35    (analog opt.)│
        └──────────┬───────────┘
                   │  ESP-NOW  (wireless, no IP)
                   ▼
        ┌──────────────────────┐            ┌───────────────────────────┐
        │   Module 2 — GATEWAY  │  WiFi/     │   BACKEND / "CLOUD"        │
        │   ESP32 #2            │  MQTT      │   Ubuntu PC (interim)      │
        │                       ├───────────▶│   Mosquitto MQTT broker    │
        │  ESP-NOW receiver     │            │   + storage + dashboard    │
        │  WiFi/MQTT publisher  │            │                            │
        │  UART out ──┐         │            │   → Raspberry Pi Zero 2 WH │
        └─────────────┼────────┘            │     (planned migration)    │
                      │ UART                 └───────────────────────────┘
                      ▼
        ┌──────────────────────┐
        │   LOCAL DISPLAY       │
        │   Arduino Uno + LCD    │
        │   (buttons switch the │
        │    on-screen view      │
        │    only — the server   │
        │    always gets the     │
        │    full dataset)       │
        └──────────────────────┘
```

**Roles**

| Device | Role | Notes |
| --- | --- | --- |
| **ESP32 #1** | Sensor node | Reads sensors, sends readings via ESP-NOW. USB-powered for now; batteries later. |
| **ESP32 #2** | Gateway | Receives from the node, publishes to MQTT over WiFi, and pushes to the Uno over UART. The concentration point — and the primary attack target. |
| **Arduino Uno** | Local display | Shows readings on the LCD. Physical buttons change the *view*, not what the server receives. |
| **Ubuntu PC** | Backend / "cloud" | Runs the Mosquitto MQTT broker, stores and displays data. Interim stand-in for the Raspberry Pi. |
| **Raspberry Pi Zero 2 WH** | Backend (planned) | Ordered but delayed; migrating the backend onto it is planned as a future write-up. |


## Bill of materials

The list below is what actually goes into the station. Small passives and the display come from an Arduino starter kit — you don't have to buy them individually if you already own a kit.

### Core boards

| Component | Qty | Role | Indicative price (PLN) |
| --- | --- | --- | --- |
| ESP32-DevKitC (ESP-WROOM-32) | 2 | Sensor node + gateway | ~50 each → ~100 |
| Arduino Uno Rev3 | 1 | Local LCD display | ~100 (original) / ~35 (compatible clone) |
| Raspberry Pi Zero 2 WH *(planned)* | 1 | Backend migration target | ~80 |

### Sensors

| Component | Qty | Measures | Indicative price (PLN) |
| --- | --- | --- | --- |
| BMP280 (I²C/SPI) | 1 | Temperature + pressure | ~10–15 |
| DHT11 | 1 | Humidity (+ rough temp) | ~8–12 |
| LM35 *(optional)* | 1 | Analog temperature (ADC exercise) | ~6–10 |
| Photoresistor (LDR) | 1 | Light intensity | ~1–2 |

### Display, interface & prototyping *(typically from a starter kit)*

| Component | Qty | Role | Indicative price (PLN) |
| --- | --- | --- | --- |
| LCD 16×2 (HD44780) | 1 | Local readout | starter-kit item |
| Push buttons | few | Switch LCD view | starter-kit item |
| Breadboard 830 pts | 1 | Prototyping | starter-kit item |
| Jumper wires (M-M / M-F / F-F) | set | Wiring | starter-kit item |
| Resistor assortment | set | Pull-ups, dividers, LEDs | starter-kit item |

### Rough total

| Build option | Estimated cost (PLN) | ≈ EUR |
| --- | --- | --- |
| Components bought individually (excl. Pi) | ~250–350 | ~€60–80 |
| Extended Arduino starter kit (~150–200) + 2× ESP32 (~100) + BMP280 (~12) | ~260–310 | ~€60–75 |

> **Pricing note.** All figures are *indicative* — based on Polish retail (Botland) around mid-2026 — and will drift over time. Prices vary a lot between original and compatible parts: an original Arduino Uno runs ~100 PLN, while a compatible clone is ~35 PLN. Treat the total as an order-of-magnitude estimate, not a quote.
> 


## Software & stack

- **Firmware:** Arduino framework / ESP-IDF on the ESP32s; standard Arduino on the Uno.
- **Node ↔ gateway link:** ESP-NOW (lightweight, connectionless, no IP layer).
- **Gateway ↔ backend:** WiFi + MQTT.
- **Broker / backend:** Mosquitto on Ubuntu (interim), moving to Raspberry Pi.
- **Gateway ↔ display:** UART.


## Repository structure

Proposed layout — evolving as the project grows:

```
.
├── experiments/            # small, self-contained learning experiments
│   ├── exp-1.0-chip-id/    #   each is a standalone PlatformIO project
│   └── exp-1.1-blink/
├── firmware/
│   ├── sensor-node/        # ESP32 #1 — sensors + ESP-NOW sender
│   ├── gateway/            # ESP32 #2 — ESP-NOW receiver + MQTT + UART
│   └── display-uno/        # Arduino Uno — LCD + buttons
├── server/
│   ├── mosquitto/          # broker config
│   └── ingest/             # storage / dashboard scripts
├── hardware/
│   ├── wiring/             # wiring diagrams & pinouts
│   └── bom.md              # detailed bill of materials
├── docs/
│   ├── architecture.md     # data flow, module responsibilities
│   ├── security-notes.md   # attack-surface observations per layer
│   ├── conventional_commits.md  # commit message convention
│   └── platformio.md       # pio CLI setup & daily commands (build/upload/monitor)
├── LICENSE
└── README.md
```


## Project status

**Early stage.** Currently focused on the hardware layer — getting sensors read reliably and the node → gateway → backend pipeline working over USB power. The IoT and security layers are added deliberately, on top of hardware that already works. Power management (LiPo, solar, charging, deep sleep) is intentionally deferred until the full data pipeline is stable.

Roughly, the sequence is:

1. **Hardware layer** *(in progress)* — sensors, ESP-NOW node → gateway, UART display, MQTT to broker.
2. **IoT layer** — networking, provisioning, OTA, the backend proper.
3. **Security layer** — attack-surface mapping and hands-on testing across the stack.


## Security notes

Even during the hardware phase, the design keeps a security lens. A few early observations (to be explored properly in later phases):

- **The gateway is the crown jewel.** It's where data concentrates and where the jump from a non-IP radio (ESP-NOW) to IP (WiFi/MQTT) happens — the natural primary target, isomorphic to real hub-and-cloud IoT systems.
- **Attack surface to probe later:** the ESP-NOW link (pairing, encryption defaults), MQTT (authentication, topic access control, TLS or lack of it), the UART channel, and OTA/provisioning as update-path vectors.
- **A concrete hardware gotcha — ADC2 vs ADC1.** On the ESP32, ADC2 becomes unreliable while WiFi is active, returning garbage values. Analog sensors (photoresistor, LM35, and any future battery-voltage divider) must therefore be wired to **ADC1 pins (GPIO 32–39)**. Worth flagging because it's the kind of quiet failure mode that produces "impossible" readings and eats hours of
debugging. (ADC non-linearity and the need for a voltage divider when measuring battery voltage are related caveats.)

> Scope: this is defensive, educational work on my own hardware. Nothing here is meant to target systems I don't own.
> 


## A note on the "learn in public" framing

I'm not writing this as an expert handing down answers — I'm documenting what I'm figuring out as I go. Some choices here are provisional and some questions are deliberately left open. If you spot something wrong or naive, that's kind of the point: corrections are welcome.


## License

MIT — see [LICENSE](LICENSE).

## Author

Tomasz Sas

QA Engineer • Creator of Testspective

https://testspective.com
