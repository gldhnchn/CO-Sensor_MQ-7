/**
 * @file CO-Sensor_MQ-7.cpp
 * @author gldhnchn (gldhnchn@posteo.de)
 * @brief main file
 * @date 2020-12-16
 *  
 */

#include "CO-Sensor_MQ-7.h"

bool ota_flag = false;
Led led(PIN_ONBOARDLED);
TaskHandle_t xHandle_do_wifi;

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
    init_wifi();
    ESP_LOGD(logtag, "Init pins %i and %i as inputs", PIN_ANALOG_INPUT, PIN_DIGITAL_INPUT);
    pinMode(PIN_ANALOG_INPUT, INPUT);
    pinMode(PIN_DIGITAL_INPUT, INPUT);
    ESP_LOGD(logtag, "Start tasks");
    create_tasks();
    //blink for telling that setup is done
    ESP_LOGD(logtag, "Init finished: blink LED");
    led.blinks();
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

    sensorValue = analogRead(PIN_ANALOG_INPUT);
    sensorValue_digital = digitalRead(PIN_DIGITAL_INPUT);
    ESP_LOGI(logtag, "sensor value: %i, %i", sensorValue, sensorValue_digital);
}

void create_tasks()
{
    xTaskCreate(
        do_wifi,            /* Task function. */
        "do_wifi",          /* name of task. */
        2048,               /* Stack size of task */
        NULL,               /* parameter of the task */
        1,                  /* priority of the task */
        &xHandle_do_wifi    /* Task handle to keep track of created task */
    );
}