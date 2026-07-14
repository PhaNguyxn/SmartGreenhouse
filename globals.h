#ifndef GLOBALS_H
#define GLOBALS_H
#include <WiFiClient.h>

struct GreenhouseData
{
    float temperature;
    float humidity;

    int soil;
    int light;

    bool autoMode; 

    bool fan;
    bool pump;
    bool lightState;
};

extern GreenhouseData greenhouse;
extern WiFiClient espClient;

#endif