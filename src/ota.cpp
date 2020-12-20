#include "ota.h"

static const char *logtag = "ota";

/**
 * @brief init ota
 * @return int 1 error, 0 success
 */
int init_ota()
{
    ESP_LOGD(logtag, "Init OTA");
    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    // ArduinoOTA.setHostname("myesp32");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            ESP_LOGI(logtag, "Start updating %s", type);
        })
        .onEnd([]() {
            ESP_LOGI(logtag, "\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            ESP_LOGI(logtag, "Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            ESP_LOGE(logtag, "Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                ESP_LOGE(logtag, "Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                ESP_LOGE(logtag, "Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                ESP_LOGE(logtag, "Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                ESP_LOGE(logtag, "Receive Failed");
            else if (error == OTA_END_ERROR)
                ESP_LOGE(logtag, "End Failed");
        });
    ESP_LOGD(logtag, "Begin OTA");
    ArduinoOTA.begin();
    return 0;
}

/**
 * @brief handle ota
 */
void handle_ota(void *parameter)
{
    ESP_LOGD(logtag, "handle ota task started");
    while(true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ArduinoOTA.handle();
    }
}