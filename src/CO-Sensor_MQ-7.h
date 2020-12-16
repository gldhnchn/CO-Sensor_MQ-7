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
#define ONBOARDLED_PIN 2

/* OTA */
#define OTA_WIFI_SSID "wlanssid"
#define OTA_WIWI_PASSWORD "wlanpassword"

/* ++++++++ */
/* includes */
#include <Arduino.h>
#include <esp_log.h>
#include "ota.h"
#include "misc.h"

/* git version */
#if __has_include("git_info.h")
#include "git_info.h"
#else
#define GIT_TAG "v0.1.3"
#endif

/* global variables*/
extern Led led;

/* function declerations */
void setup();
void loop();
#endif // COSensor_MQ7
