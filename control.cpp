#include "control.h"

#include "config.h"
#include "globals.h"

#include <Arduino.h>

void initOutputs()
{
    pinMode(FAN_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(GROWLIGHT_PIN, OUTPUT);

    greenhouse.fan = false;
    greenhouse.pump = false;
    greenhouse.lightState = false;

    digitalWrite(FAN_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
    digitalWrite(GROWLIGHT_PIN, LOW);
}

void autoControl()
{
    if (!greenhouse.autoMode)
    {
        return;
    }

    if (greenhouse.temperature >= TEMP_FAN_ON ||
        greenhouse.humidity >= HUMIDITY_FAN_ON)
    {
        greenhouse.fan = true;
    }
    else if (greenhouse.temperature <= TEMP_FAN_OFF &&
             greenhouse.humidity <= HUMIDITY_FAN_OFF)
    {
        greenhouse.fan = false;
    }

    if (greenhouse.soil <= SOIL_PUMP_ON)
    {
        greenhouse.pump = true;
    }
    else if (greenhouse.soil >= SOIL_PUMP_OFF)
    {
        greenhouse.pump = false;
    }

    if (greenhouse.light < LIGHT_GROW_ON)
    {
        greenhouse.lightState = true;
    }
    else if (greenhouse.light > LIGHT_GROW_OFF)
    {
        greenhouse.lightState = false;
    }
}

void updateOutputs()
{
    digitalWrite(
        FAN_PIN,
        greenhouse.fan ? HIGH : LOW
    );

    digitalWrite(
        PUMP_PIN,
        greenhouse.pump ? HIGH : LOW
    );

    digitalWrite(
        GROWLIGHT_PIN,
        greenhouse.lightState ? HIGH : LOW
    );
}