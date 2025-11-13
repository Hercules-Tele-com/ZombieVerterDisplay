# Display Configuration Guide

This project supports multiple display configurations using conditional compilation. You can easily switch between different displays by editing a single configuration file.

## Supported Displays

### 1. SPI Display (320x170)
- Uses TFT_eSPI library
- Original configuration for smaller SPI-based displays
- Lower resolution, suitable for compact projects

### 2. Waveshare ESP32-S3-Touch-LCD-7 (800x480)
- Uses ESP32_Display_Panel library
- 7-inch RGB parallel interface display
- High resolution with capacitive touch (GT911)
- Model: ESP32-S3-Touch-LCD-7
- Display Controller: ST7262 / EK9716
- Touch Controller: GT911 (I2C)

## How to Switch Displays

### Step 1: Edit `display_config.h`

Open the file `/ZombieVerterDisplay/display_config.h` and find this section near the top:

```cpp
// *******************************************************
// ** SELECT YOUR DISPLAY HERE - UNCOMMENT ONE OPTION **
// *******************************************************

// Option 1: Original 320x170 SPI Display (using TFT_eSPI)
//#define USE_SPI_DISPLAY

// Option 2: Waveshare ESP32-S3-Touch-LCD-7 (800x480 RGB Display)
#define USE_WAVESHARE_7INCH_RGB

// *******************************************************
```

**To use the SPI display:**
- Comment out `#define USE_WAVESHARE_7INCH_RGB` by adding `//` in front
- Uncomment `#define USE_SPI_DISPLAY` by removing `//`

**To use the Waveshare 7" RGB display:**
- Comment out `#define USE_SPI_DISPLAY` by adding `//` in front
- Uncomment `#define USE_WAVESHARE_7INCH_RGB` by removing `//`

### Step 2: Install Required Libraries

#### For SPI Display:
- TFT_eSPI
- LVGL (v8.3.x)

#### For Waveshare 7" RGB Display:
- ESP32_Display_Panel (v0.1.4 or later)
- ESP32_IO_Expander (v0.0.3)
- LVGL (v8.3.x)

You can install these through the Arduino Library Manager.

### Step 3: Configure TFT_eSPI (SPI Display Only)

If using the SPI display, you'll need to configure TFT_eSPI for your specific hardware:
1. Locate the TFT_eSPI library folder in your Arduino libraries directory
2. Edit `User_Setup.h` or create a custom setup file
3. Configure the pins according to your hardware (see `pin_config.h`)

### Step 4: Compile and Upload

After selecting your display configuration:
1. **Clean build** (recommended): Delete the `build` folder if it exists
2. **Compile**: Verify your sketch in Arduino IDE
3. **Upload**: Flash to your ESP32 device

## Technical Details

### Display Resolutions

| Display Type | Width | Height | Interface | Library |
|-------------|-------|--------|-----------|---------|
| SPI Display | 320   | 170    | SPI       | TFT_eSPI |
| Waveshare 7" | 800   | 480    | RGB Parallel | ESP32_Display_Panel |

### Pin Configurations

#### Waveshare ESP32-S3-Touch-LCD-7 Pin Mapping

**RGB Data Lines (16-bit RGB565):**
- DATA0-DATA15: GPIO 14, 38, 18, 17, 10, 39, 0, 45, 48, 47, 21, 1, 2, 42, 41, 40

**Control Signals:**
- HSYNC: GPIO 46
- VSYNC: GPIO 3
- DE (Data Enable): GPIO 5
- PCLK (Pixel Clock): GPIO 7

**Touch Interface (I2C):**
- SDA: GPIO 8
- SCL: GPIO 9

**Timing Parameters:**
- Pixel Clock: 16 MHz
- Horizontal: HPW=4, HBP=8, HFP=8
- Vertical: VPW=4, VBP=8, VFP=8

#### SPI Display Pin Mapping

Configured in `pin_config.h`:
- PIN_LCD_BL: GPIO 15 (Backlight)
- PIN_LCD_DC: GPIO 13 (Data/Command)
- PIN_LCD_CS: GPIO 10 (Chip Select)
- PIN_LCD_CLK: GPIO 12 (Clock)
- PIN_LCD_MOSI: GPIO 11 (Data Out)
- PIN_LCD_RES: GPIO 9 (Reset)

## LVGL Configuration

The project uses LVGL v8.3.x for the user interface. Buffer sizes and display parameters are automatically adjusted based on the selected display:

- **SPI Display**: Buffer size = (320 × 170) / 13
- **Waveshare 7"**: Uses RGB frame buffers with anti-tearing mode

### LVGL Anti-Tearing (Waveshare RGB Only)

The Waveshare configuration uses LVGL direct-mode with anti-tearing to eliminate screen tearing:
- Mode: Direct-mode (fastest, recommended)
- Frame Buffers: 2 (double-buffering)
- Bounce Buffer: 800 × 10 pixels

You can adjust these settings in `lvgl_port_v8.h` if needed.

## UI Scaling Considerations

The UI was originally designed for 320×170 resolution. When using the 800×480 Waveshare display:

### Current Behavior:
- UI elements maintain their original size
- More screen real estate is available
- Text and graphics remain sharp

### Future Enhancements:
If you want to scale the UI for the larger display, you can:
1. **Redesign in SquareLine Studio**: Create a new 800×480 layout
2. **Manual scaling**: Adjust object sizes and positions in `ui.c`
3. **Font sizes**: Use larger LVGL fonts for better readability

## Troubleshooting

### Compilation Errors

**Error: "No display configuration selected"**
- Solution: Make sure you've uncommented exactly ONE display option in `display_config.h`

**Error: "Exactly one display driver must be selected"**
- Solution: Only one display option should be uncommented. Check that you don't have both enabled.

**Error: Missing library errors**
- Solution: Install the required libraries for your selected display (see Step 2 above)

### Display Issues

**Blank screen on Waveshare display:**
1. Check that all GPIO pins are correctly wired
2. Verify PSRAM is enabled in Arduino IDE: Tools → PSRAM → "OPI PSRAM"
3. Ensure you're using ESP32-S3 board definition
4. Check serial output for initialization errors

**Screen tearing on Waveshare display:**
- The anti-tearing mode should prevent this
- If you still see tearing, try changing `LVGL_PORT_AVOID_TEARING_MODE` in `lvgl_port_v8.h`

**SPI display not working:**
1. Verify TFT_eSPI is configured correctly
2. Check pin definitions in `pin_config.h`
3. Ensure SPI bus is not in use by other peripherals

### Touch Issues (Waveshare only)

**Touch not responding:**
1. Verify I2C pins are correct (SDA=GPIO8, SCL=GPIO9)
2. Check that `ESP_OPEN_TOUCH` is set to 1 in `display_config.h`
3. Scan I2C bus to verify GT911 is detected at address 0x5D or 0x14

## Performance Tips

### For Waveshare 7" Display:
- **Enable PSRAM**: Essential for large frame buffers
- **Use OPI PSRAM mode**: Faster than QPI mode on ESP32-S3
- **CPU Frequency**: Set to 240 MHz for best performance
- **Partition scheme**: Use "16MB Flash (3MB APP/9.9MB FATFS)" or similar

### For SPI Display:
- **Buffer in SRAM**: Better performance than PSRAM for SPI
- **DMA**: TFT_eSPI uses DMA by default for faster transfers
- **SPI Speed**: Configure in TFT_eSPI User_Setup.h

## Serial Debug Output

When the display initializes, you'll see information printed to Serial:
```
Display Configuration: Waveshare_7inch_RGB
Resolution: 800x480
Initializing ESP_Panel...
Initializing LCD...
Initializing Touch...
Initializing LVGL...
ESP_Panel display initialized
DisplayManager Setup Complete
```

This confirms which display configuration is active.

## Advanced Configuration

### Modifying Display Parameters

All display-specific parameters are in `display_config.h`. You can adjust:
- **RGB timing parameters** (for Waveshare): Clock speed, blanking periods
- **Buffer sizes**: LVGL_BUFFER_DIVIDER controls memory usage
- **Touch settings**: I2C speed, pull-ups, etc.

### Custom Display Support

To add support for another display:
1. Add a new `#define USE_YOUR_DISPLAY` section in `display_config.h`
2. Set appropriate DISPLAY_WIDTH, DISPLAY_HEIGHT, and other parameters
3. Implement initialization in `DisplayManager::Setup()` using conditional compilation
4. Add required libraries to DisplayManager.h

## Project Structure

```
ZombieVerterDisplay/
├── display_config.h          # Display selection and configuration
├── DisplayManager.h           # Display manager header
├── DisplayManager.cpp         # Display initialization and management
├── lvgl_port_v8.h            # LVGL porting layer header (Waveshare)
├── lvgl_port_v8.cpp          # LVGL porting layer implementation (Waveshare)
├── pin_config.h              # Pin definitions (SPI display)
├── ZombieVerterDisplay.ino   # Main application
└── ui.c / ui.h               # LVGL UI definition files
```

## Version History

- **v2.0**: Added multi-display support with conditional compilation
- **v1.0**: Original version with 320×170 SPI display

## Support

For issues or questions:
1. Check the troubleshooting section above
2. Review the Waveshare wiki: https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-7
3. Check ESP32_Display_Panel documentation
4. Check LVGL documentation: https://docs.lvgl.io/8.3/

## License

See project LICENSE file for details.
