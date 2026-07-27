#include "sensor.h"
#include "control.h"
#include "display.h"
#include "globals.h"
#include "wifi.h"
#include "mqtt.h"

constexpr unsigned long UPDATE_INTERVAL_MS = 2000;

unsigned long lastUpdateTime = 0;

void setup()
{
    Serial.begin(115200);

    initSensors();
    initOutputs();
    initDisplay();
    initWiFi();
    initMQTT();

}

void loop()
{

    handleMQTT();

    unsigned long currentTime = millis();

    if (
        currentTime - lastUpdateTime <
        UPDATE_INTERVAL_MS
    )
    {
        delay(10);
        return;
    }

    lastUpdateTime = currentTime;

    readSensors();

    autoControl();

    updateOutputs();

    updateDisplay();

    publishData();

}