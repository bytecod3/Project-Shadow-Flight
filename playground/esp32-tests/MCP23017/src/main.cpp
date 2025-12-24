#include <Arduino.h>
#include <Wire.h>
#include "mcp23017.h"

#define addr 0x20

MCP23017_IO io_expander(addr);

#define LED0 0
#define LED1 1
#define LED2 2
#define LED9 9 // B1

void setup() {
    Serial.begin(115200);
    delay(50);

    Wire.begin(21, 22);

    if(io_expander.init()) {
        Serial.println("MCP expander found");
    } else {
        Serial.println("expander not found");
    }

    io_expander.pin_mode(LED0, OUTPUT);
    io_expander.pin_mode(LED1, OUTPUT);
    io_expander.pin_mode(LED2, OUTPUT); 
    io_expander.pin_mode(LED9, OUTPUT);

    io_expander.digital_write(LED0, HIGH);
    io_expander.digital_write(LED1, HIGH);
    io_expander.digital_write(LED2, HIGH);
    io_expander.digital_write(LED9, HIGH);

    // input pins 
    io_expander.pin_mode(7, INPUT);
}

bool led_state = 0;
void loop() {

    static unsigned long last_millis;
    if( (millis() - last_millis ) > 200) {
        led_state = !led_state;
        io_expander.digital_write(LED0, led_state);
        last_millis = millis();
    }

    byte x = io_expander.digital_read(7);
    if(!x) 
    {
        Serial.println("Pressed");
    } else {
        Serial.println("Not pressed");
    }

}