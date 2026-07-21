#ifndef CONFIG_H
#define CONFIG_H

// Các chân điều khiển
#define DHT_PIN         4
#define DHT_TYPE        DHT22

#define SOIL_PIN        34
#define LIGHT_PIN       35
#define FAN_PIN         26
#define PUMP_PIN        27
#define GROWLIGHT_PIN   2

// Quạt: điều khiển theo nhiệt độ
constexpr float TEMP_FAN_ON  = 30.0f;
constexpr float TEMP_FAN_OFF = 27.0f;

// Quạt: điều khiển theo độ ẩm không khí
constexpr float HUMIDITY_FAN_ON  = 80.0f;
constexpr float HUMIDITY_FAN_OFF = 70.0f;

// Máy bơm: điều khiển theo độ ẩm đất
constexpr int SOIL_PUMP_ON  = 35;
constexpr int SOIL_PUMP_OFF = 55;

// Đèn: điều khiển theo ánh sáng 0–100%
constexpr int LIGHT_GROW_ON  = 30;
constexpr int LIGHT_GROW_OFF = 50;

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