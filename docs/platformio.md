# PlatformIO CLI — setup & daily commands

Quick reference for building, uploading and monitoring any PlatformIO
sub-project in this repo (`experiments/*`, `firmware/sensor-node`,
`firmware/gateway`, ...). Run all commands from inside the sub-project's
folder (the one containing its `platformio.ini`).

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

- `pio run -t upload` - builds and flashes the firmware to the connected board.
- `pio device monitor` - opens the serial monitor (baud rate comes from the
  project's `platformio.ini`, typically 115200 for the boards in this repo).

Other commands worth knowing:

```
pio run              # build only, no upload
pio device list      # list connected serial ports
```
