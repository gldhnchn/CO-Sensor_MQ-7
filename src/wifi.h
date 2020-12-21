#include "CO-Sensor_MQ-7.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <esp_log.h>

void init_wifi();
void handle_wifi(void *parameter);