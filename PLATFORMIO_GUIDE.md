# PlatformIO Build Guide

This project supports both **Arduino IDE** and **PlatformIO**. This guide covers building and running the project with PlatformIO.

## Quick Start

### 1. Install PlatformIO

**Option A: PlatformIO Core (CLI)**
```bash
pip install platformio
```

**Option B: PlatformIO IDE (VSCode Extension)**
- Install Visual Studio Code
- Install the "PlatformIO IDE" extension
- Restart VSCode

### 2. Open Project

```bash
cd ZombieVerterDisplay
```

If using VSCode, open the folder in VSCode after installing PlatformIO IDE extension.

### 3. Build and Upload

#### For Waveshare ESP32-S3-Touch-LCD-7 (Default):
```bash
# Build
pio run -e waveshare_7inch

# Upload
pio run -e waveshare_7inch -t upload

# Monitor serial output
pio device monitor -e waveshare_7inch

# Build + Upload + Monitor (all in one)
pio run -e waveshare_7inch -t upload && pio device monitor
```

#### For SPI Display:
```bash
# Build
pio run -e spi_display

# Upload
pio run -e spi_display -t upload

# Monitor
pio device monitor -e spi_display
```

#### Using Default Environment:
```bash
# Build (uses default_envs = waveshare_7inch from platformio.ini)
pio run

# Upload
pio run -t upload

# Monitor
pio device monitor
```

## Build Environments

The project includes 4 build environments:

| Environment | Display | Debug | Description |
|------------|---------|-------|-------------|
| `waveshare_7inch` | Waveshare 7" RGB | No | Production build for Waveshare |
| `spi_display` | SPI 320×170 | No | Production build for SPI display |
| `waveshare_7inch_debug` | Waveshare 7" RGB | Yes | Debug build with verbose logging |
| `spi_display_debug` | SPI 320×170 | Yes | Debug build with verbose logging |

## Configuration

### Switching Displays

**Method 1: Use Different Environments (Recommended)**

No code changes needed! Just specify the environment:
```bash
pio run -e waveshare_7inch    # Waveshare display
pio run -e spi_display         # SPI display
```

**Method 2: Edit platformio.ini Default**

Change the default environment in `platformio.ini`:
```ini
[platformio]
default_envs = spi_display    # Change this line
```

Then just run:
```bash
pio run    # Uses the default environment
```

### Custom Serial Port

If your device is not auto-detected, edit `platformio.ini`:

```ini
[env:waveshare_7inch]
upload_port = /dev/ttyUSB0      ; Linux/Mac
; upload_port = COM3             ; Windows
monitor_port = /dev/ttyUSB0     ; Linux/Mac
; monitor_port = COM3            ; Windows
```

### Memory and Performance Settings

The environments are pre-configured with optimal settings:

**Waveshare 7" RGB:**
- OPI PSRAM enabled
- 240 MHz CPU
- 16MB Flash with large app partition
- QIO flash mode for speed

**SPI Display:**
- 240 MHz CPU
- Standard flash settings
- Smaller app partition

## Library Management

PlatformIO automatically manages all dependencies defined in `platformio.ini`.

### Waveshare Display Libraries:
- ESP32_Display_Panel (^0.1.4)
- ESP32_IO_Expander (^0.0.3)
- LVGL (^8.3.11)
- ArduinoJson, AsyncTCP, ESPAsyncWebServer, AsyncElegantOTA

### SPI Display Libraries:
- TFT_eSPI (^2.5.43)
- LVGL (^8.3.11)
- ArduinoJson, AsyncTCP, ESPAsyncWebServer, AsyncElegantOTA

### Updating Libraries

```bash
# Update all libraries to latest compatible versions
pio pkg update

# Update specific library
pio pkg update --library "ESP32_Display_Panel"
```

## Debugging

### Enable Debug Build

Use the debug environments:
```bash
pio run -e waveshare_7inch_debug -t upload
pio device monitor -e waveshare_7inch_debug
```

Debug builds include:
- Verbose ESP32 core logging
- WiFi debug output
- Optimization disabled (-O0)
- Debug symbols included (-g)

### Serial Monitor

The project uses 115200 baud rate with these filters enabled:
- `esp32_exception_decoder` - Decodes stack traces
- `colorize` - Colors output for readability
- `time` - Adds timestamps

```bash
# Monitor with all filters
pio device monitor

# Monitor without filters
pio device monitor --filter direct

# Monitor with custom baud rate
pio device monitor -b 115200
```

## Filesystem (SPIFFS/LittleFS)

The project uses LittleFS for web server files (`SPIFFS` folder).

### Upload Filesystem

```bash
# Upload filesystem to device
pio run -t uploadfs -e waveshare_7inch
```

### Build Filesystem Image

```bash
# Just build the filesystem image (don't upload)
pio run -t buildfs
```

## VSCode Integration

When using PlatformIO IDE in VSCode:

### Build Tasks
- Press `Ctrl+Alt+B` (or Cmd+Alt+B on Mac) to build
- Or use the checkmark icon in the bottom toolbar

### Upload
- Press `Ctrl+Alt+U` (or Cmd+Alt+U on Mac) to upload
- Or use the arrow icon in the bottom toolbar

### Monitor
- Click the "plug" icon in the bottom toolbar
- Or use the PlatformIO: Monitor task

### Switch Environment
- Click the environment name in the bottom toolbar
- Select a different environment from the list

### IntelliSense
PlatformIO automatically configures IntelliSense for the ESP32-S3, so you'll get:
- Code completion
- Error highlighting
- Go to definition
- Documentation on hover

## Common Commands

```bash
# Clean build
pio run -t clean

# Clean all environments
pio run --target clean --environment waveshare_7inch
pio run --target clean --environment spi_display

# Show project info
pio project config

# List connected devices
pio device list

# Check for library updates
pio pkg outdated

# Install missing dependencies
pio pkg install
```

## Troubleshooting

### Build Errors

**Error: "Could not find the package with 'esp-arduino-libs/ESP32_Display_Panel' requirements"**

Solution: Update the PlatformIO platform:
```bash
pio pkg update
pio platform update espressif32
```

**Error: "PSRAM not found"**

Solutions:
1. Make sure you're using ESP32-S3 board with PSRAM
2. Check `platformio.ini` has `board_build.psram_type = opi`
3. Try: `pio run -e waveshare_7inch -t clean` then rebuild

**Error: Multiple definition errors**

Solution: Clean and rebuild:
```bash
pio run -t clean
pio run
```

### Upload Errors

**Error: "Serial port not found"**

Solutions:
1. Check USB cable is data-capable (not charge-only)
2. Install CH340/CP2102 drivers if needed
3. Check device permissions on Linux: `sudo usermod -a -G dialout $USER`
4. Specify port manually in `platformio.ini`

**Error: "Timed out waiting for packet header"**

Solutions:
1. Hold BOOT button while connecting USB
2. Press RESET button after connecting
3. Try lower upload speed: `upload_speed = 460800`

### Runtime Errors

**Display shows nothing:**
1. Check `pio device monitor` for error messages
2. Verify correct environment is selected
3. Ensure PSRAM is enabled for Waveshare display
4. Check wiring and connections

**Touch not working:**
1. Verify I2C pins in serial output
2. Enable debug build to see I2C scan results
3. Check GT911 initialization messages

## Advanced Configuration

### Custom Build Flags

Add custom flags in `platformio.ini`:

```ini
[env:my_custom_env]
extends = env:waveshare_7inch
build_flags =
    ${env:waveshare_7inch.build_flags}
    -DMY_CUSTOM_FLAG=1
    -DLOG_LEVEL=5
```

### Partition Scheme

To use a custom partition scheme:

1. Create `partitions_custom.csv` in project root
2. Update `platformio.ini`:
   ```ini
   board_build.partitions = partitions_custom.csv
   ```

### Library Overrides

To use a specific library version:

```ini
lib_deps =
    ${env.lib_deps}
    ESP32_Display_Panel@0.1.4    ; Specific version
    ; or
    ESP32_Display_Panel@^0.1.4   ; Compatible with 0.1.x
```

## Continuous Integration (CI)

Example GitHub Actions workflow:

```yaml
name: PlatformIO CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        environment: [waveshare_7inch, spi_display]

    steps:
    - uses: actions/checkout@v3
    - uses: actions/cache@v3
      with:
        path: |
          ~/.cache/pip
          ~/.platformio/.cache
        key: ${{ runner.os }}-pio
    - uses: actions/setup-python@v4
      with:
        python-version: '3.11'
    - name: Install PlatformIO
      run: pip install platformio
    - name: Build
      run: pio run -e ${{ matrix.environment }}
```

## Comparison: PlatformIO vs Arduino IDE

| Feature | PlatformIO | Arduino IDE |
|---------|-----------|-------------|
| **Library Management** | Automatic per project | Global, manual |
| **Build Speed** | Faster (incremental) | Slower (rebuilds more) |
| **Multiple Environments** | Built-in | Manual switching |
| **IntelliSense** | Excellent | Basic |
| **CLI Support** | Full featured | Limited |
| **Board Selection** | platformio.ini | GUI |
| **Debug Support** | Native | Limited |
| **Dependency Isolation** | Per-project | Global |

## Getting Help

### PlatformIO Resources:
- Documentation: https://docs.platformio.org/
- Community: https://community.platformio.org/
- GitHub: https://github.com/platformio/platformio-core

### Project-Specific Help:
- See `DISPLAY_CONFIG_README.md` for display configuration
- Check serial output for initialization messages
- Review `platformio.ini` comments for configuration options

## VSCode Recommended Extensions

When using PlatformIO in VSCode, these extensions are helpful:

- **PlatformIO IDE** (required)
- **C/C++** (Microsoft) - Enhanced IntelliSense
- **Error Lens** - Inline error messages
- **GitLens** - Git integration
- **Better Comments** - Colored comments

## Tips and Tricks

### Fast Development Cycle

```bash
# Watch mode: automatically rebuild on file changes
pio run -t upload && pio device monitor &
# Then edit files - it will auto-rebuild and show output
```

### Multiple Boards

If you have both displays connected:

```bash
# Terminal 1: Waveshare display
pio run -e waveshare_7inch -t upload
pio device monitor -p /dev/ttyUSB0

# Terminal 2: SPI display
pio run -e spi_display -t upload
pio device monitor -p /dev/ttyUSB1
```

### Memory Analysis

```bash
# Show memory usage
pio run -e waveshare_7inch -t size

# Detailed memory map
pio run -e waveshare_7inch -v
```

### Precompiled Headers

For faster compilation, PlatformIO uses precompiled headers automatically.

## Migration from Arduino IDE

If you're moving from Arduino IDE to PlatformIO:

1. **No code changes needed!** The same code works in both.
2. Install PlatformIO (see Quick Start above)
3. Open the project folder in VSCode/PIO
4. Select your environment
5. Click Build (checkmark icon)

**Benefits of switching:**
- Faster builds
- Better code completion
- Easy library management
- CLI automation
- Better debugging

## Conclusion

PlatformIO provides a more streamlined and powerful development experience compared to Arduino IDE, especially for projects with multiple configurations like this one.

The automatic environment switching makes it trivial to build for different displays without editing any configuration files.

Happy coding! 🚀
