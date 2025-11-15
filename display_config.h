/*
 * Display Configuration Header
 *
 * Simplified configuration for use with ESP32_Display_Panel library's
 * built-in board support.
 */

#pragma once

// Display selection for conditional compilation
#if defined(USE_WAVESHARE_7INCH_RGB)
    #define DISPLAY_TYPE_NAME "Waveshare_7inch_RGB"
    #define DISPLAY_WIDTH  800
    #define DISPLAY_HEIGHT 480
    #define USE_TFT_ESPI 0
    #define USE_ESP_PANEL 1

#elif defined(USE_SPI_DISPLAY)
    #define DISPLAY_TYPE_NAME "SPI_320x170"
    #define DISPLAY_WIDTH  320
    #define DISPLAY_HEIGHT 170
    #define USE_TFT_ESPI 1
    #define USE_ESP_PANEL 0
    #define LVGL_BUFFER_DIVIDER 13

#else
    // Default to Waveshare for Arduino IDE
    #define DISPLAY_TYPE_NAME "Waveshare_7inch_RGB"
    #define DISPLAY_WIDTH  800
    #define DISPLAY_HEIGHT 480
    #define USE_TFT_ESPI 0
    #define USE_ESP_PANEL 1
#endif

// Validation
#if (USE_TFT_ESPI + USE_ESP_PANEL) != 1
    #error "Exactly one display driver must be selected!"
#endif
