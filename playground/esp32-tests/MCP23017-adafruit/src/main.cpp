#include <Arduino.h>
#include <Wire.h>
#include "mcp23017.h"

#define addr 0x20

MCP23017_IO io_expander(addr);

void setup() {
    Serial.begin(115200);
    delay(50);

    Wire.begin(21, 22);

    if(io_expander.init()) {
        Serial.println("MCP expander found");
    } else {
        Serial.println("expander not found");
    }

    io_expander.pin_mode(0, OUTPUT);
    io_expander.digital_write(0, HIGH);
}

void loop() {

}