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
TaskHandle_t    xHandle_handle_wifi,
                xHandle_handle_ota;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
std::string  sensor_value_msg;
int sensorValue = 0;
int sensorValue_digital = 0;
struct tm timeinfo;

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
    init_ota();
    ESP_LOGD(logtag, "Init pins %i and %i as inputs", PIN_ANALOG_INPUT, PIN_DIGITAL_INPUT);
    pinMode(PIN_ANALOG_INPUT, INPUT);
    pinMode(PIN_DIGITAL_INPUT, INPUT);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    create_tasks();
    //blink for telling that setup is done
    ESP_LOGD(logtag, "Init finished: blink LED");
    led.blinks();
}

/**
 * @brief arduino loop
 * This is the arduino loop function.
 */
void loop()
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    sensorValue = analogRead(PIN_ANALOG_INPUT);
    sensorValue_digital = digitalRead(PIN_DIGITAL_INPUT);
    getLocalTime(&timeinfo);
    char buf[sizeof("2020-12-21T18:30:54+0100")];
    strftime(buf, sizeof(buf), "%FT%T%z", &timeinfo);
    std::string timeStr(buf),
                sensorValueStr(String(sensorValue).c_str()),
                sensorValue_digitalStr(String(sensorValue_digital).c_str());
    sensor_value_msg = timeStr + ", " + sensorValueStr + ", " + sensorValue_digitalStr;
    ESP_LOGV(sensor_value_msg.c_str());
}

void create_tasks()
{
    ESP_LOGD(logtag, "Start tasks");
    xTaskCreate(
        handle_wifi,            /* Task function. */
        "handle_wifi",          /* name of task. */
        2048,                   /* Stack size of task */
        NULL,                   /* parameter of the task */
        1,                      /* priority of the task */
        &xHandle_handle_wifi    /* Task handle to keep track of created task */
    );
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(
        handle_ota,             /* Task function. */
        "handle_ota",           /* name of task. */
        2048,                   /* Stack size of task */
        NULL,                   /* parameter of the task */
        1,                      /* priority of the task */
        &xHandle_handle_ota     /* Task handle to keep track of created task */
    );
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGD(logtag, "All tasks started");
}