#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "globals.h"
#include "control.h"

void callback(char* topic, byte* payload, unsigned int length);
void publishDeviceStates();

PubSubClient mqttClient(espClient);

void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to MQTT...");

        if (mqttClient.connect(MQTT_CLIENT_ID))
        {
            Serial.println(" connected");

            mqttClient.subscribe("greenhouse/control/fan");
            mqttClient.subscribe("greenhouse/control/pump");
            mqttClient.subscribe("greenhouse/control/light");
            mqttClient.subscribe("greenhouse/control/auto");

            publishDeviceStates();
        }
        else
        {
            Serial.print(" failed, state = ");
            Serial.println(mqttClient.state());

            delay(2000);
        }
    }
}

void initMQTT()
{
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);
}


void publishDeviceStates()
{
    if (!mqttClient.connected())
    {
        return;
    }

    mqttClient.publish(
        "greenhouse/status/fan",
        greenhouse.fan ? "1" : "0",
        true
    );

    mqttClient.publish(
        "greenhouse/status/pump",
        greenhouse.pump ? "1" : "0",
        true
    );

    mqttClient.publish(
        "greenhouse/status/light",
        greenhouse.lightState ? "1" : "0",
        true
    );

    mqttClient.publish(
        "greenhouse/status/auto",
        greenhouse.autoMode ? "1" : "0",
        true
    );
}


void publishData()
{
    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }

    mqttClient.publish(
        "greenhouse/temp",
        String(greenhouse.temperature, 1).c_str()
    );

    mqttClient.publish(
        "greenhouse/humidity",
        String(greenhouse.humidity, 1).c_str()
    );

    mqttClient.publish(
        "greenhouse/light",
        String(greenhouse.light).c_str()
    );

    mqttClient.publish(
        "greenhouse/soil",
        String(greenhouse.soil).c_str()
    );

    publishDeviceStates();
}


void callback(char* topic, byte* payload, unsigned int length)
{
    String message;

    for (unsigned int i = 0; i < length; i++)
    {
        message += static_cast<char>(payload[i]);
    }

    message.trim();

    String receivedTopic = String(topic);

    Serial.print("MQTT received: ");
    Serial.print(receivedTopic);
    Serial.print(" = ");
    Serial.println(message);

   
    if (receivedTopic == "greenhouse/control/auto")
    {
        greenhouse.autoMode = (message == "1");

        if (greenhouse.autoMode)
        {
            autoControl();
        }

        updateOutputs();

        publishDeviceStates();

        return;
    }

    if (greenhouse.autoMode)
    {
        Serial.println(
            "Manual command ignored because Auto Mode is ON"
        );

        publishDeviceStates();
        return;
    }

    if (receivedTopic == "greenhouse/control/fan")
    {
        greenhouse.fan = (message == "1");
    }
    else if (receivedTopic == "greenhouse/control/pump")
    {
        greenhouse.pump = (message == "1");
    }
    else if (receivedTopic == "greenhouse/control/light")
    {
        greenhouse.lightState = (message == "1");
    }
    else
    {
        return;
    }

    updateOutputs();

    publishDeviceStates();
}