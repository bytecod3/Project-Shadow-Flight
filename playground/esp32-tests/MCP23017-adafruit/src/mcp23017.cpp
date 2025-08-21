#include <Arduino.h>
#include <Wire.h>
#include "mcp23017.h"

/**
 * @brief This function initializes the MCP23017
 * @ret True if init OK, false otherwise
 */
uint8_t MCP23017_IO::init(uint8_t DEV_ADDR) {
    uint8_t init_status = Wire.begin(DEV_ADDR);

    if (init_status == true) {
        Wire.beginTransmission(DEV_ADDR);
        // send the init sequence 
        // for (size_t i = 0; i < INIT_SEQ_LENGTH; i++)
        // {
        //     Wire.write(init_sequence[i]); // push to the I2C buffer 
        // }
        Wire.endTransmission(true);
    }

    return init_status;

}