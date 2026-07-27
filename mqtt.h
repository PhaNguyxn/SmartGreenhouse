#ifndef MQTT_H
#define MQTT_H

void initWiFi();
void initMQTT();

void handleMQTT();

void reconnectMQTT();

void publishData();

void publishDeviceStates();

#endif