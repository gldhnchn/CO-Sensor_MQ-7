/**
 * @file CO-Sensor_MQ-7.h
 * @author gldhnchn (gldhnchn@posteo.de)
 * @brief main file
 * @date 2020-12-16
 * 
 */
#ifndef COSensor_MQ7
#define COSensor_MQ7

/* ++++++ */
/* config */
#include <string>
#define PIN_ONBOARDLED 2
#define PIN_ANALOG_INPUT 35
#define PIN_DIGITAL_INPUT 34

/* OTA */
#define WIFI_SSID "wlanssid"
#define WIFI_PASSWORD "wlanpassword"
#define WIFI_HOSTNAME "ESP32_MQ_7_CO_Sensor"
#define WIFI_PORT 42000

/* ++++++++ */
/* includes */
#include <Arduino.h>
#include <esp_log.h>
#include "ota.h"
#include "misc.h"
#include "wifi.h"
#include "time.h"
#include <string>

/* git version */
#if __has_include("git_info.h")
#include "git_info.h"
#else
#define GIT_TAG "v0.0.0"
#endif

/* global variables*/
extern Led led;
extern TaskHandle_t xHandle_handle_wifi,
                    xHandle_handle_ota;
extern std::string  sensor_value_msg;

/* function declerations */
void setup();
void loop();
void create_tasks();
#endif // COSensor_MQ7
