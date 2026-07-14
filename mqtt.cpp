#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "globals.h"

void callback(char* topic, byte* payload, unsigned int length);

PubSubClient mqttClient(espClient);

void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        mqttClient.connect(MQTT_CLIENT_ID);

        mqttClient.subscribe("greenhouse/control/fan");
        mqttClient.subscribe("greenhouse/control/pump");
        mqttClient.subscribe("greenhouse/control/light");
        mqttClient.subscribe("greenhouse/control/auto");

        delay(1000);
    }
}

void initMQTT()
{
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);
}

void publishData()
{
    if (!mqttClient.connected())
        reconnectMQTT();

    mqttClient.loop();

    mqttClient.publish(
        "greenhouse/temp",
        String(greenhouse.temperature).c_str());

    mqttClient.publish(
        "greenhouse/humidity",
        String(greenhouse.humidity).c_str());

    mqttClient.publish(
        "greenhouse/light",
        String(greenhouse.light).c_str());

    mqttClient.publish(
        "greenhouse/soil",
        String(greenhouse.soil).c_str());

    mqttClient.publish(
        "greenhouse/fan",
        greenhouse.fan ? "1" : "0");

    mqttClient.publish(
        "greenhouse/pump",
        greenhouse.pump ? "1" : "0");

    mqttClient.publish(
        "greenhouse/lightState",
        greenhouse.lightState ? "1" : "0");

    mqttClient.publish(
    "greenhouse/status/fan",
    greenhouse.fan ? "1":"0");

    mqttClient.publish(
        "greenhouse/status/pump",
        greenhouse.pump ? "1":"0");

    mqttClient.publish(
        "greenhouse/status/light",
        greenhouse.lightState ? "1":"0");

    mqttClient.publish(
    "greenhouse/auto",
    greenhouse.autoMode ? "1" : "0");
}

void callback(char* topic, byte* payload, unsigned int length)
{
    String msg = "";

    for (int i = 0; i < length; i++)
    {
        msg += (char)payload[i];
    }

    if(String(topic)=="greenhouse/control/fan")
    {
        if(greenhouse.autoMode)
            return;

        greenhouse.fan = (msg=="1");
    }

    if (String(topic) == "greenhouse/control/pump")
    {
        greenhouse.pump = (msg == "1");
        digitalWrite(PUMP_PIN, greenhouse.pump);
    }

    if (String(topic) == "greenhouse/control/light")
    {
        greenhouse.lightState = (msg == "1");
        digitalWrite(GROWLIGHT_PIN, greenhouse.lightState);
    }

    if(String(topic)=="greenhouse/control/auto")
    {
        greenhouse.autoMode = (msg=="1");
    }
}