/**
 * @file COSensor_MQ7.h
 * @author gldhnchn (gldhnchn@posteo.de)
 * @brief main file
 * @date 2020-12-16
 * 
 */
#ifndef COSensor_MQ7
#define COSensor_MQ7

/* ++++++ */
/* config */
#define PIN_ONBOARDLED 2
#define PIN_ANALOG_INPUT 35
#define PIN_DIGITAL_INPUT 34

/* OTA */
#define OTA_WIFI_SSID "wlanssid"
#define OTA_WIWI_PASSWORD "wlanpassword"
#define WIFI_HOSTNAME "ESP32_MQ_7_CO_Sensor"

/* ++++++++ */
/* includes */
#include <Arduino.h>
#include <esp_log.h>
#include "ota.h"
#include "misc.h"
#include "wifi.h"

/* git version */
#if __has_include("git_info.h")
#include "git_info.h"
#else
#define GIT_TAG "v0.0.0"
#endif

/* global variables*/
extern Led led;
extern TaskHandle_t xHandle_do_wifi;

/* function declerations */
void setup();
void loop();
void create_tasks();
#endif // COSensor_MQ7
