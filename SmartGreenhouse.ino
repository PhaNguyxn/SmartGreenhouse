#include "sensor.h"
#include "control.h"
#include "display.h"
#include "globals.h"
#include "wifi.h"
#include "mqtt.h"

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
    readSensors();

    autoControl();

    updateOutputs();

    updateDisplay();

    publishData();

    Serial.println("--------------------");

    Serial.print("Temperature : ");
    Serial.println(greenhouse.temperature);

    Serial.print("Humidity : ");
    Serial.println(greenhouse.humidity);

    Serial.print("Soil : ");
    Serial.println(greenhouse.soil);

    Serial.print("Light : ");
    Serial.println(greenhouse.light);

    Serial.print("Fan : ");
    Serial.println(greenhouse.fan);

    Serial.print("Pump : ");
    Serial.println(greenhouse.pump);

    Serial.print("Grow Light : ");
    Serial.println(greenhouse.lightState);

    delay(2000);
}