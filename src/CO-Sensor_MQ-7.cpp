/**
 * @file CO-Sensor_MQ-7.cpp
 * @author gldhnchn (gldhnchn@posteo.de)
 * @brief main file
 * @date 2020-12-16
 *  
 */

#include "CO-Sensor_MQ-7.h"

bool ota_flag = false;
Led led(ONBOARDLED_PIN);

/**
 * @brief arduino setup
 * This is the arduino setup function. It is run once at startup.
 * Inits are done here and RTOS tasks are started here.
 */
void setup()
{
    const char *logtag = "setup";
    esp_log_level_set("*", ESP_LOG_DEBUG);

    Serial.begin(115200);

    ESP_LOGI(logtag, "*******************************************");
    ESP_LOGI(logtag, "Hello, this is CO-Sensor_MQ-7.");
    ESP_LOGI(logtag, "Firmware version: %s", GIT_TAG);
    ESP_LOGI(logtag, "*******************************************");

    // ESP_LOGD(logtag, "Read OTA flag");
    // ESP_LOGD(logtag, "OTA flag: %i", ota_flag);
    if (ota_flag)
    {
    //     ESP_LOGI(logtag, "Entering OTA mode");
    //     ESP_LOGI(logtag, "Setting OTA flag to 0");
    //     init_ota(OTA_WIFI_SSID, OTA_WIWI_PASSWORD);
    }
    else
    {
        ESP_LOGD(logtag, "Entering normal mode, starting init...");
        pinMode(12, INPUT);
        pinMode(14, INPUT);
        //blink for telling that setup is done
        ESP_LOGD(logtag, "Init finished: blink LED");
        led.blinks();
    }
}

/**
 * @brief arduino loop
 * This is the arduino loop function. It is not used, instead RTOS tasks are used.
 * That's why the loop task is delayed max. When OTA flag is set to active during boot, this loop is used for handling OTA.
 * 
 */
int sensorValue = 0;
int sensorValue_digital = 0;

void loop()
{
    if (ota_flag)
        handle_ota();
    else
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    sensorValue = analogRead(12);
    sensorValue_digital = digitalRead(14);
    ESP_LOGI(logtag, "sensor value: %i, %i", sensorValue, sensorValue_digital);
}