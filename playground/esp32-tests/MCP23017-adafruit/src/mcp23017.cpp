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
    uint8_t init_status = Wire.begin(this->_dev_address);

    if (init_status == true) {
        Wire.beginTransmission(this->_dev_address);
        uint8_t data_frame[3];

        // set mode to 16bit, sequential
        data_frame[0] = this->_dev_address; // device opcode
        data_frame[1] = IOCONA_BANK_0; // 0x0A -> address when bank is 0
        data_frame[2] = 0x00; // sequential addressing, address pointer increments 

        // send the init sequence 
        for (size_t i = 0; i < 3; i++)
        {
            Wire.write(data_frame[i]); // push to the I2C buffer 
        }

        Wire.endTransmission(true); // write to slave
    }

    return init_status;

}

/**
 * @brief This function sets the pinMode 
 * @param pin pin t set 
 * @param mode pin direction, 1 for input, 0 for output
 * 
 */
void MCP23017_IO::set_pin_mode(uint8_t pin, uint8_t mode) {
    // todo: check if object is valid
    Wire.beginTransmission(this->_dev_address);

    uint8_t data_frame[3];
    uint8_t _m;

    // clear LSB to set as write 
    this->_dev_address &= ~(1 << 0); // set write bit
    data_frame[0] = this->_dev_address;

    uint8_t port = (pin < 8) ? 0 : 1;

    // register to write 
    data_frame[1] = 0x09;

    // if(pin > 15) { 
    //     pin %= 16;
    // } 
    // if(mode > 2) {
    //     mode %= 3;
    // }

    /**
     * An input is set as 1
     * an output is set as 0
     */
    if(mode == 0) { 
        // set as output
        _m &= ~(1 << pin);
    } else {
        // set as input
        _m |= (1 << pin);
    }

    data_frame[2] = _m;   


    for (size_t i = 0; i < 3; i++)
    {
        Wire.write(data_frame[i]);
    }
    
    Wire.endTransmission(true);    

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
    Wire.beginTransmission(this->_dev_address);

    uint8_t data_frame[2];
    data_frame[0] = 0x00; // IODIR A

    // check pin 
    // check level
    // check mode 

    data_frame[1] = 0x00;

    for (size_t i = 0; i < 2; i++)
    {
        Wire.write(data_frame[i]);
    }

    Wire.endTransmission(true);
    

}