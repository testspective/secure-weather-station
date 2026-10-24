# Experiment 1.0 - Chip ID

First-contact experiment for the ESP32 DevKit board. It checks that the toolchain,
upload and serial monitor all work, and that GPIO output drives an LED.

The firmware ([src/main.cpp](src/main.cpp)) demonstrates three things:

1. **Onboard LED blink** - the DevKit's built-in LED on GPIO2 blinks with a
   250 ms half-period (500 ms full on/off cycle).
2. **External LED blink** - an added green LED on GPIO4 (anode) with a 330 ohm
   series resistor on the cathode side to GND. It blinks at half the speed,
   500 ms half-period. GPIO2 therefore blinks twice as fast as GPIO4. Both run on
   non-blocking `millis()` timers.
3. **Chip info over serial** - on boot, `setup()` prints chip model, silicon
   revision, core count, CPU frequency, flash size, eFuse MAC and SDK version to
   the serial monitor at 115200 baud.

## Wiring

| From (ESP32) | Via | To | Notes |
| --- | --- | --- | --- |
| GPIO2 | - | Onboard LED | No external wiring. GPIO2 is a strapping pin - do not add a pull-up here. |
| GPIO4 | - | Green LED anode (long leg) | Direct connection to the GPIO pin. |
| Green LED cathode (short leg) | 330 ohm resistor | GND | Series resistor on the low side limits current to ~3-4 mA at 3.3 V. |
| USB | - | Host PC | Power + serial monitor (115200 baud). |

## Prerequisites

`pio` must be available in your terminal's PATH. Installing the VS Code
**PlatformIO IDE** extension installs PlatformIO Core to
`~/.platformio/penv/Scripts` (Windows) / `~/.platformio/penv/bin` (macOS/Linux),
but does **not** add it to a regular terminal's PATH - it only works inside
VS Code's dedicated "PlatformIO Core CLI" terminal (sidebar icon > PIO Home,
or Command Palette > "PlatformIO: New Terminal").

If you get `pio: command not found` / `'pio' is not recognized` in a plain
terminal, either:

- Use VS Code's PlatformIO CLI terminal (no setup needed), or
- Add the PlatformIO `Scripts`/`bin` folder to your PATH once, permanently:
  ```powershell
  # Windows PowerShell, current user
  [Environment]::SetEnvironmentVariable('Path', [Environment]::GetEnvironmentVariable('Path','User') + ';' + "$HOME\.platformio\penv\Scripts", 'User')
  ```
  ```sh
  # macOS/Linux (bash/zsh), add to your shell profile
  export PATH="$HOME/.platformio/penv/bin:$PATH"
  ```
  Restart your terminal afterwards and confirm with `pio --version`.

## Run

```
pio run -t upload
pio device monitor
```

Expected: both LEDs blink (GPIO2 twice as fast as GPIO4), and the
`=== Who am I? ===` chip info block appears once in the serial monitor.
