#ifndef CONFIG_H
#define CONFIG_H

//SENSOR PIN

#define DHT_PIN         4
#define DHT_TYPE        DHT22

#define SOIL_PIN        34
#define LIGHT_PIN       35

//OUTPUT PIN

#define FAN_PIN         26
#define PUMP_PIN        27
#define GROWLIGHT_PIN   2

//AUTO MODE

#define TEMP_LIMIT      30

#define SOIL_LIMIT      40

#define LIGHT_LIMIT     30

//OLED

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

// WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// MQTT
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883

#define MQTT_CLIENT_ID "ESP32_GREENHOUSE"

#define MQTT_SUB_TOPIC "greenhouse/control"


#endif