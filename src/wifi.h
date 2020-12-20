#include "CO-Sensor_MQ-7.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <esp_log.h>

void do_wifi(void *parameter);
void init_wifi();
void handle_wifi();