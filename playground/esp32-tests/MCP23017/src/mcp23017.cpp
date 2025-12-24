#include <Arduino.h>
#include <Wire.h>
#include "mcp23017.h"

MCP23017_IO::MCP23017_IO(uint8_t address) {
    this->_dev_address = address;
}

/**
 * @brief This function initializes the MCP23017
 * @ret True if init OK, false otherwise
 */
uint8_t MCP23017_IO::init() {
    Wire.beginTransmission(this->_dev_address);
    uint8_t error = Wire.endTransmission(true);
    
    return !error;
}

/**
 * @brief This function sets the pinMode 
 * @param pin pin t set 
 * @param mode pin direction, 1 for input, 0 for output
 * 
 */
void MCP23017_IO::pin_mode(uint8_t pin, uint8_t mode) {
    // check which port to write to 
    uint8_t reg;
    uint8_t p;
    reg = (pin < 8) ? IODIRA : IODIRB; // todo: put into helper

    p = pin % 8; // loopback for next port // todo: put into helper
    
    // read the intended register  //todo: put into helper 
    uint8_t reg_value;
    Wire.beginTransmission(this->_dev_address);
    Wire.write(reg);
    Wire.endTransmission(false); // do not interrupt the reading from the same device 
    Wire.requestFrom(this->_dev_address, 1); // request 1 byte from device
    reg_value = Wire.read();

    /**
     * set the value for that particular pin passed
     * INPUT -> 1 (set)
     * OUTPUT -> 0 (clear)
     * 
     * INPUT is an inbuilt macro on Arduino
     */
    if(mode == INPUT) {
        reg_value |= (1 <<p); 
    } else if (mode == OUTPUT) {
        reg_value &= ~(1 << p);
    }

    // write the register with new value 
    Wire.beginTransmission(this->_dev_address);
    Wire.write(reg); // register address
    Wire.write(reg_value); // register value 
    Wire.endTransmission(true); // end transmission, no restart

}

// uint8_t MCP23017_IO::resolve_register(uint8_t base, uint8_t pin = 0) {
//     uint8_t reg_addr = base;
//     if(pin < 8) {
//         return reg_addr;
//     } else {
//         reg_addr = reg_addr;
//     }

// }

void MCP23017_IO::digital_write(uint8_t pin, uint8_t level) {
  
    uint8_t reg;
    uint8_t reg_value;
    uint8_t p = pin % 8; // check which pin we need to write 

    // read the current state of the GPIO
    reg = (pin < 8) ? OLATA : OLATB; // get register address
    Wire.beginTransmission(this->_dev_address);
    Wire.write(reg);
    Wire.endTransmission(false); // do not interrupt the reading from the same device 
    Wire.requestFrom(this->_dev_address, 1); // request 1 byte from device
    reg_value = Wire.read();

    // set pin and direction 
    if(level == HIGH) {
        // set bit 
        reg_value |= (1 << p);
    } else {
        // clear bit 
        reg_value &= ~(1 << p);
    }

    // send to slave device 
    Wire.beginTransmission(this->_dev_address);
    Wire.write(reg);
    Wire.write(reg_value);
    Wire.endTransmission(true);

}

uint8_t MCP23017_IO::digital_read(uint8_t pin) {
    // resolve the register bank (A or B)
    uint8_t reg = (pin < 8) ? GPIOA : GPIOB;
    uint8_t reg_value;
    uint8_t pin_val;
    
    // read the GPIO via I2C
    Wire.beginTransmission(this->_dev_address);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(this->_dev_address, (uint8_t)1);
    reg_value = Wire.read();
    Wire.endTransmission(true);
    
    uint8_t val = (reg_value >> pin) & 0x01;
    return val;
}