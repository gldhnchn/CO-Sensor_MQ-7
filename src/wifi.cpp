#include "wifi.h"

WiFiServer server(42000);
static const char *logtag = "wifi";

/**
 * @brief Handle wifi events.
 * @param parameter just a dummy parameter
 */
void handle_wifi(void *parameter)
{
    ESP_LOGD(logtag, "handle wifi task started");
    while(true)
    {
        ESP_LOGV(logtag, "listen to new wifi clients");
        WiFiClient client = server.available();   // listen for incoming clients
        if(client)
        {
            ESP_LOGD(logtag, "new wifi client");
            while (client.connected())
            {
                led.light_on();
                ESP_LOGD(logtag, "sending msg to client: %s", sensor_value_msg.c_str());
                client.println(sensor_value_msg.c_str());
                led.light_off();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            ESP_LOGD(logtag, "disconnect client");
            client.stop();
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
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
    ESP_LOGD(logtag, "Begin WiFi server");
    server.begin();
    return;
}