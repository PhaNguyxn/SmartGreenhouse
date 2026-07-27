#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "globals.h"
#include "control.h"

void callback(
    char* topic,
    byte* payload,
    unsigned int length
);

PubSubClient mqttClient(espClient);

bool parseState(String message)
{
    message.trim();
    message.toLowerCase();

    return (
        message == "1" ||
        message == "true" ||
        message == "on"
    );
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
        greenhouse.lightState
            ? "1"
            : "0",
        true
    );

    mqttClient.publish(
        "greenhouse/status/auto",
        greenhouse.autoMode
            ? "1"
            : "0",
        true
    );
}


void reconnectMQTT()
{
    while (
        WiFi.status() == WL_CONNECTED &&
        !mqttClient.connected()
    )
    {
        Serial.print(
            "Connecting to MQTT..."
        );

        String clientId =
            String(MQTT_CLIENT_ID) +
            "-" +
            String(
                static_cast<uint32_t>(
                    ESP.getEfuseMac()
                ),
                HEX
            );

        if (
            mqttClient.connect(
                clientId.c_str()
            )
        )
        {
            Serial.println(" connected");

            // Đăng ký nhận lệnh điều khiển
            mqttClient.subscribe(
                "greenhouse/control/fan"
            );

            mqttClient.subscribe(
                "greenhouse/control/pump"
            );

            mqttClient.subscribe(
                "greenhouse/control/light"
            );

            mqttClient.subscribe(
                "greenhouse/control/auto"
            );

            publishDeviceStates();
        }
        else
        {
            Serial.print(
                " failed, MQTT state = "
            );

            Serial.println(
                mqttClient.state()
            );

            delay(1000);
        }
    }
}

void initMQTT()
{
    mqttClient.setServer(
        MQTT_SERVER,
        MQTT_PORT
    );

    mqttClient.setCallback(callback);
}

void handleMQTT()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }

    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }

    mqttClient.loop();
}



void publishData()
{
    if (!mqttClient.connected())
    {
        return;
    }

    String temperature =
        String(
            greenhouse.temperature,
            1
        );

    String humidity =
        String(
            greenhouse.humidity,
            1
        );

    String light =
        String(greenhouse.light);

    String soil =
        String(greenhouse.soil);

    mqttClient.publish(
        "greenhouse/temp",
        temperature.c_str()
    );

    mqttClient.publish(
        "greenhouse/humidity",
        humidity.c_str()
    );

    mqttClient.publish(
        "greenhouse/light",
        light.c_str()
    );

    mqttClient.publish(
        "greenhouse/soil",
        soil.c_str()
    );

    publishDeviceStates();
}

void callback(
    char* topic,
    byte* payload,
    unsigned int length
)
{
    String message;

    for (
        unsigned int i = 0;
        i < length;
        i++
    )
    {
        message +=
            static_cast<char>(
                payload[i]
            );
    }

    message.trim();
    message.toLowerCase();

    String receivedTopic =
        String(topic);

    bool requestedState =
        parseState(message);


    if (
        receivedTopic ==
        "greenhouse/control/auto"
    )
    {
        greenhouse.autoMode =
            requestedState;

        Serial.print("Auto Mode: ");
        Serial.println(
            greenhouse.autoMode
                ? "ON"
                : "OFF"
        );

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
            "Manual command ignored "
            "because Auto Mode is ON"
        );

        publishDeviceStates();

        return;
    }

    if (
        receivedTopic ==
        "greenhouse/control/fan"
    )
    {
        greenhouse.fan =
            requestedState;

        Serial.print("Fan changed to: ");
        Serial.println(
            greenhouse.fan
                ? "ON"
                : "OFF"
        );
    }
    else if (
        receivedTopic ==
        "greenhouse/control/pump"
    )
    {
        greenhouse.pump =
            requestedState;

        Serial.print("Pump changed to: ");
        Serial.println(
            greenhouse.pump
                ? "ON"
                : "OFF"
        );
    }
    else if (
        receivedTopic ==
        "greenhouse/control/light"
    )
    {
        greenhouse.lightState =
            requestedState;

        Serial.print(
            "Grow Light changed to: "
        );

        Serial.println(
            greenhouse.lightState
                ? "ON"
                : "OFF"
        );
    }
    else
    {
        return;
    }

    updateOutputs();

    publishDeviceStates();
}