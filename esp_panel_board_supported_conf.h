/**
 * esp_panel_board_supported_conf.h
 *
 * Configuration for ESP32_Display_Panel library to use the built-in
 * Waveshare ESP32-S3-Touch-LCD-7 board support.
 */

#pragma once

/**
 * Follow the steps to configure the ESP Panel:
 *
 * 1. Uncomment the macro corresponding to the board you are using, such as
 *    `BOARD_WAVESHARE_ESP32_S3_TOUCH_LCD_7`
 */

// Enable the Waveshare ESP32-S3-Touch-LCD-7 board configuration
#define BOARD_WAVESHARE_ESP32_S3_TOUCH_LCD_7    (1)

// Additional LVGL and display settings
#define ESP_PANEL_USE_LCD                   (1)         // Enable LCD
#define ESP_PANEL_USE_TOUCH                 (0)         // Disable touch for now (testing)

// LVGL port settings for anti-tearing with RGB display
#define LVGL_PORT_AVOID_TEAR                (1)         // Enable to avoid tearing effect
#define LVGL_PORT_ROTATION_DEGREE           (0)         // Display rotation in degrees
