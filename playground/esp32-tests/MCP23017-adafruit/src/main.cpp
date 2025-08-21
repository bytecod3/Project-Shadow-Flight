#include <Arduino.h>
#include "mcp23017.h"

MCP23017_IO io_expander;
#define addr 0x20

void setup() {
    Serial.begin(115200);
    delay(50);

    if(io_expander.init(addr)) {
        Serial.println("MCP expander found");
    } else {
        Serial.println("expander not found");
    }
}

void loop() {

}