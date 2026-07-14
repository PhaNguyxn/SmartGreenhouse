#include "sensor.h"

#include "config.h"
#include "globals.h"

#include <Arduino.h>
#include <DHT.h>

DHT dht(DHT_PIN, DHT_TYPE);

void initSensors()
{
    dht.begin();

    pinMode(SOIL_PIN, INPUT);

    pinMode(LIGHT_PIN, INPUT);
}

void readSensors()
{
    greenhouse.temperature = dht.readTemperature();

    greenhouse.humidity = dht.readHumidity();

    int soilRaw = analogRead(SOIL_PIN);

    greenhouse.soil = map(
        soilRaw,
        0,
        4095,
        100,
        0
    );

    int lightRaw = analogRead(LIGHT_PIN);

    greenhouse.light = map(
        lightRaw,
        0,
        4095,
        0,
        100
    );
}