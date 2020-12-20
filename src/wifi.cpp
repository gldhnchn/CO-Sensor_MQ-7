#include "wifi.h"

static const char *logtag = "wifi";

/**
 * @brief Handle wifi events.
 * @param parameter just a dummy parameter
 */
void handle_wifi(void *parameter)
{
    ESP_LOGD(logtag, "do wifi task started");
    while(true)
    {
        vTaskDelay(portMAX_DELAY); /*wait as much as possible ... */
    }
    return;
}

/**
 * @brief Establish wifi connection.
 */
void init_wifi()
{
    ESP_LOGD(logtag, "Init Wifi");
    ESP_LOGD(logtag, "Set WiFi mode");
    WiFi.mode(WIFI_STA);
    ESP_LOGD(logtag, "Set WiFi host name to %s", WIFI_HOSTNAME);
    WiFi.setHostname(WIFI_HOSTNAME);
    ESP_LOGD(logtag, "Begin WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        ESP_LOGD(lagtag, "Waiting for connection.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(lagtag, "Connection established!");
    ESP_LOGI(logtag, "IP address: %ui", WiFi.localIP());
    return;
}