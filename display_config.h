/*
 * Display Configuration Header
 *
 * This file allows you to switch between different display configurations
 * by changing a single define.
 *
 * Compatible with both Arduino IDE and PlatformIO:
 * - Arduino IDE: Manually uncomment one option below
 * - PlatformIO: Automatically set by environment (see platformio.ini)
 */

#pragma once

// *******************************************************
// ** SELECT YOUR DISPLAY HERE - UNCOMMENT ONE OPTION **
// *******************************************************
// Note: When using PlatformIO, these are set automatically
// by the build environment and you don't need to edit this file.

#if !defined(USE_SPI_DISPLAY) && !defined(USE_WAVESHARE_7INCH_RGB)
    // Default selection for Arduino IDE (only used if not set by PlatformIO)

    // Option 1: Original 320x170 SPI Display (using TFT_eSPI)
    //#define USE_SPI_DISPLAY

    // Option 2: Waveshare ESP32-S3-Touch-LCD-7 (800x480 RGB Display)
    #define USE_WAVESHARE_7INCH_RGB
#endif

// *******************************************************

// Display-specific configurations
#if defined(USE_SPI_DISPLAY)
    // Original SPI Display Configuration
    #define DISPLAY_TYPE_NAME "SPI_320x170"
    #define DISPLAY_WIDTH  320
    #define DISPLAY_HEIGHT 170
    #define USE_TFT_ESPI 1
    #define USE_ESP_PANEL 0
    #define LVGL_BUFFER_DIVIDER 13  // Buffer size = width * height / divider
    #define ESP_OPEN_TOUCH 0        // Touch disabled for SPI display

#elif defined(USE_WAVESHARE_7INCH_RGB)
    // Waveshare ESP32-S3-Touch-LCD-7 RGB Display Configuration
    #define DISPLAY_TYPE_NAME "Waveshare_7inch_RGB"
    #define DISPLAY_WIDTH  800
    #define DISPLAY_HEIGHT 480
    #define USE_TFT_ESPI 0
    #define USE_ESP_PANEL 1
    #define LVGL_BUFFER_DIVIDER 10  // Buffer size = width * height / divider
    #define ESP_OPEN_TOUCH 1        // Touch enabled for Waveshare display

    // Waveshare ESP32-S3-Touch-LCD-7 specific settings
    #define ESP_PANEL_USE_CUSTOM_BOARD       (1)

    // LCD Configuration
    #define ESP_PANEL_USE_LCD                (1)
    #define ESP_PANEL_LCD_NAME               ST7262
    #define ESP_PANEL_LCD_WIDTH              (800)
    #define ESP_PANEL_LCD_HEIGHT             (480)

    // LCD Bus Settings - RGB Interface
    #define ESP_PANEL_LCD_BUS_SKIP_INIT_HOST    (0)
    #define ESP_PANEL_LCD_BUS_TYPE              (ESP_PANEL_BUS_TYPE_RGB)

    // RGB Bus Parameters
    #define ESP_PANEL_LCD_RGB_CLK_HZ            (16 * 1000 * 1000)
    #define ESP_PANEL_LCD_RGB_HPW               (4)
    #define ESP_PANEL_LCD_RGB_HBP               (8)
    #define ESP_PANEL_LCD_RGB_HFP               (8)
    #define ESP_PANEL_LCD_RGB_VPW               (4)
    #define ESP_PANEL_LCD_RGB_VBP               (8)
    #define ESP_PANEL_LCD_RGB_VFP               (8)
    #define ESP_PANEL_LCD_RGB_PCLK_ACTIVE_NEG   (1)
    #define ESP_PANEL_LCD_RGB_DATA_WIDTH        (16)
    #define ESP_PANEL_LCD_RGB_PIXEL_BITS        (16)
    #define ESP_PANEL_LCD_RGB_FRAME_BUF_NUM     (2)
    #define ESP_PANEL_LCD_RGB_BOUNCE_BUF_SIZE   (ESP_PANEL_LCD_WIDTH * 10)

    // RGB GPIO Pins
    #define ESP_PANEL_LCD_RGB_IO_HSYNC          (46)
    #define ESP_PANEL_LCD_RGB_IO_VSYNC          (3)
    #define ESP_PANEL_LCD_RGB_IO_DE             (5)
    #define ESP_PANEL_LCD_RGB_IO_PCLK           (7)
    #define ESP_PANEL_LCD_RGB_IO_DISP           (-1)
    #define ESP_PANEL_LCD_RGB_IO_DATA0          (14)
    #define ESP_PANEL_LCD_RGB_IO_DATA1          (38)
    #define ESP_PANEL_LCD_RGB_IO_DATA2          (18)
    #define ESP_PANEL_LCD_RGB_IO_DATA3          (17)
    #define ESP_PANEL_LCD_RGB_IO_DATA4          (10)
    #define ESP_PANEL_LCD_RGB_IO_DATA5          (39)
    #define ESP_PANEL_LCD_RGB_IO_DATA6          (0)
    #define ESP_PANEL_LCD_RGB_IO_DATA7          (45)
    #define ESP_PANEL_LCD_RGB_IO_DATA8          (48)
    #define ESP_PANEL_LCD_RGB_IO_DATA9          (47)
    #define ESP_PANEL_LCD_RGB_IO_DATA10         (21)
    #define ESP_PANEL_LCD_RGB_IO_DATA11         (1)
    #define ESP_PANEL_LCD_RGB_IO_DATA12         (2)
    #define ESP_PANEL_LCD_RGB_IO_DATA13         (42)
    #define ESP_PANEL_LCD_RGB_IO_DATA14         (41)
    #define ESP_PANEL_LCD_RGB_IO_DATA15         (40)

    // LCD Color Settings
    #define ESP_PANEL_LCD_COLOR_BITS            (16)
    #define ESP_PANEL_LCD_BGR_ORDER             (0)
    #define ESP_PANEL_LCD_INEVRT_COLOR          (0)

    // LCD Transformation Flags
    #define ESP_PANEL_LCD_SWAP_XY               (0)
    #define ESP_PANEL_LCD_MIRROR_X              (0)
    #define ESP_PANEL_LCD_MIRROR_Y              (0)

    // LCD Reset Pin
    #define ESP_PANEL_LCD_IO_RST                (-1)
    #define ESP_PANEL_LCD_RST_LEVEL             (0)

    // Touch Configuration
    #define ESP_PANEL_USE_TOUCH                 (ESP_OPEN_TOUCH)
    #define ESP_PANEL_TOUCH_NAME                GT911
    #define ESP_PANEL_TOUCH_H_RES               (ESP_PANEL_LCD_WIDTH)
    #define ESP_PANEL_TOUCH_V_RES               (ESP_PANEL_LCD_HEIGHT)

    // Touch Bus Settings
    #define ESP_PANEL_TOUCH_BUS_SKIP_INIT_HOST  (0)
    #define ESP_PANEL_TOUCH_BUS_TYPE            (ESP_PANEL_BUS_TYPE_I2C)
    #define ESP_PANEL_TOUCH_BUS_HOST_ID         (0)
    #define ESP_PANEL_TOUCH_I2C_ADDRESS         (0)
    #define ESP_PANEL_TOUCH_I2C_CLK_HZ          (400 * 1000)
    #define ESP_PANEL_TOUCH_I2C_SCL_PULLUP      (1)
    #define ESP_PANEL_TOUCH_I2C_SDA_PULLUP      (1)
    #define ESP_PANEL_TOUCH_I2C_IO_SCL          (9)
    #define ESP_PANEL_TOUCH_I2C_IO_SDA          (8)

    // Touch Transformation Flags
    #define ESP_PANEL_TOUCH_SWAP_XY             (0)
    #define ESP_PANEL_TOUCH_MIRROR_X            (0)
    #define ESP_PANEL_TOUCH_MIRROR_Y            (0)

    // Touch Reset and Interrupt Pins
    #define ESP_PANEL_TOUCH_IO_RST              (-1)
    #define ESP_PANEL_TOUCH_RST_LEVEL           (0)
    #define ESP_PANEL_TOUCH_IO_INT              (-1)
    #define ESP_PANEL_TOUCH_INT_LEVEL           (0)

    // I2C Master Configuration (shared with touch)
    #define I2C_MASTER_SCL_IO                   (9)
    #define I2C_MASTER_SDA_IO                   (8)
    #define I2C_MASTER_NUM                      I2C_NUM_0
    #define I2C_MASTER_FREQ_HZ                  (400000)
    #define I2C_MASTER_TX_BUF_DISABLE           (0)
    #define I2C_MASTER_RX_BUF_DISABLE           (0)
    #define I2C_MASTER_TIMEOUT_MS               (1000)

#else
    #error "No display configuration selected! Please uncomment one display option in display_config.h"
#endif

// Validation
#if (USE_TFT_ESPI + USE_ESP_PANEL) != 1
    #error "Exactly one display driver must be selected!"
#endif
