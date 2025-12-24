#ifndef MCP23017_H
#define MCP23017_H

#include <stdint.h>

/**
 * 
 * IO PORT A registers - BANK 0
 * 
 * todo: name registers
 */
static uint8_t IODIRA        = 0x00;
static uint8_t IOPOLA        = 0x02;
static uint8_t GPINTENA      = 0x04;
static uint8_t DEFVALA       = 0x06;
static uint8_t INTCONA       = 0x08;
static uint8_t IOCON         = 0x0A;
static uint8_t GPPUA         = 0x0C;
static uint8_t INTFA         = 0x0E;
static uint8_t INTCAPA       = 0x10;
static uint8_t GPIOA         = 0x12;
static uint8_t OLATA         = 0x14;

static uint8_t IODIRB        = 0x01;
static uint8_t IOPOLB        = 0x03;
static uint8_t GPINTENB      = 0x05;
static uint8_t DEFVALB       = 0x07;
static uint8_t INTCONB       = 0x09;
static uint8_t GPPUB         = 0x0D;
static uint8_t INTFB         = 0x0F;
static uint8_t INTCAPB       = 0x11;
static uint8_t GPIOB         = 0x13;
static uint8_t OLATB         = 0x15;

#define INIT_SEQ_LENGTH 4

class MCP23017_IO{
    private:  
    uint8_t _dev_address;  

    public:

    MCP23017_IO(uint8_t address);

    /**
     * Init sequence 
     * Start, OPCODE, Write, Address
     */
    uint8_t init_sequence[INIT_SEQ_LENGTH]; 

    /**
     * @brief This function initializes MCP23017 in I2C mode
     */
    uint8_t init();
    uint8_t read_register(uint8_t address, uint8_t data);
    uint8_t write_register(uint8_t address, uint8_t* buffer);
    void pin_mode(uint8_t pin, uint8_t mode);
    uint8_t digital_read(uint8_t pin);
    void digital_write(uint8_t pin, uint8_t level);
    uint8_t read_port(uint8_t port);
    //uint8_t MCP23017_IO_set_interrupts();
    //uint8_t MCP23017_IO_setup_interrupt_pin();
    void MCP23017_IO_reset();
    uint8_t resolve_register(uint8_t base, uint8_t pin = 0);

};

#endif