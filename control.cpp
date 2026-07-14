#include "control.h"

#include "config.h"
#include "globals.h"

#include <Arduino.h>

void initOutputs()
{
    pinMode(FAN_PIN,OUTPUT);

    pinMode(PUMP_PIN,OUTPUT);

    pinMode(GROWLIGHT_PIN,OUTPUT);

    digitalWrite(FAN_PIN,LOW);

    digitalWrite(PUMP_PIN,LOW);

    digitalWrite(GROWLIGHT_PIN,LOW);
}

void autoControl()
{
    if(!greenhouse.autoMode)
        return;

    greenhouse.fan =
        greenhouse.temperature > TEMP_LIMIT;

    greenhouse.pump =
        greenhouse.soil < SOIL_LIMIT;

    greenhouse.lightState =
        greenhouse.light < LIGHT_LIMIT;
}

void updateOutputs()
{
    digitalWrite(FAN_PIN,
                 greenhouse.fan);

    digitalWrite(PUMP_PIN,
                 greenhouse.pump);

    digitalWrite(GROWLIGHT_PIN,
                 greenhouse.lightState);
}