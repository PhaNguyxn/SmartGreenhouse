#include "display.h"
#include "globals.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

void initDisplay()
{
    Wire.begin(21,22);

    if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
    {
        Serial.println("OLED failed");
        while(true);
    }

    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);

    display.setCursor(0,0);

    display.println("SMART GREENHOUSE");

    display.display();

    delay(1500);
}

void updateDisplay()
{
    display.clearDisplay();

    display.setCursor(0,0);

    display.setTextSize(1);

    display.println("SMART GREENHOUSE");

    display.println();

    display.print("Temp : ");
    display.print(greenhouse.temperature);
    display.println(" C");

    display.print("Hum  : ");
    display.print(greenhouse.humidity);
    display.println(" %");

    display.print("Soil : ");
    display.print(greenhouse.soil);
    display.println(" %");

    display.print("Light: ");
    display.println(greenhouse.light);

    display.display();
}