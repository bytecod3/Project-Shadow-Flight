#ifndef MCP23017_H
#define MCP23017_H

#include <stdint.h>

/**
 * IO PORT A registers - BANK 0
 * 
 * todo: name registers
 */
static uint8_t IODIRA_BANK_0        = 0x00;
static uint8_t IOPOLA_BANK_0        = 0x02;
static uint8_t GPINTENA_BANK_0      = 0x04;
static uint8_t DEFVALA_BANK_0       = 0x06;
static uint8_t INTCONA_BANK_0       = 0x08;
static uint8_t IOCONA_BANK_0        = 0x0A;
static uint8_t GPPUA_BANK_0         = 0x0C;
static uint8_t INTFA_BANK_0         = 0x0E;
static uint8_t INTCAPA_BANK_0       = 0x10;
static uint8_t GPIOA_BANK_0         = 0x12;
static uint8_t OLATA_BANK_0         = 0x14;

/**
 * IO PORT B registers - BANK 1
 */
static uint8_t IODIRB_BANK_0 = 0x01;
static uint8_t IOPOLB_BANK_0 = 0x03;
static uint8_t GPINTENB_BANK_0 = 0x05;
static uint8_t DEFVALB_BANK_0 = 0x07;
static uint8_t INTCONB_BANK_0 = 0x09;
static uint8_t IOCONB_BANK_0 = 0x0B;
static uint8_t GPPUB_BANK_0 = 0x0D;
static uint8_t INTFB_BANK_0 = 0x0F;
static uint8_t INTCAPB_BANK_0 = 0x11;
static uint8_t GPIOB_BANK_0 = 0x13;
static uint8_t OLATB_BANK_0 = 0x15;

/**
 * IO PORT A registers - BANK 1
 */
static uint8_t IODIRA_BANK_1        = 0x00;
static uint8_t IOPOLA_BANK_1        = 0x01;
static uint8_t GPINTENA_BANK_1      = 0x02;
static uint8_t DEFVALA_BANK_1       = 0x03;
static uint8_t INTCONA_BANK_1       = 0x04;
static uint8_t IOCONA_BANK_1        = 0x05;
static uint8_t GPPUA_BANK_1         = 0x06;
static uint8_t INTFA_BANK_1         = 0x07;
static uint8_t INTCAPA_BANK_1       = 0x08;
static uint8_t GPIOA_BANK_1         = 0x09;
static uint8_t OLATA_BANK_1         = 0x0A;

/**
 * IO PORT B registers - BANK 1
 */
static uint8_t IODIRB_BANK_1 = 0x10;
static uint8_t IOPOLB_BANK_1 = 0x11;
static uint8_t GPINTENB_BANK_1 = 0x12;
static uint8_t DEFVALB_BANK_1 = 0x13;
static uint8_t INTCONB_BANK_1 = 0x14;
static uint8_t IOCONB_BANK_1 = 0x15;
static uint8_t GPPUB_BANK_1 = 0x16;
static uint8_t INTFB_BANK_1 = 0x17;
static uint8_t INTCAPB_BANK_1 = 0x18;
static uint8_t GPIOB_BANK_1 = 0x19;
static uint8_t OLATB_BANK_1 = 0x1A;

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
    void set_pin_mode(uint8_t pin, uint8_t mode);
    uint8_t digital_read(uint8_t pin);
    uint8_t digital_write(uint8_t pin);
    uint8_t read_port(uint8_t port);
    //uint8_t MCP23017_IO_set_interrupts();
    //uint8_t MCP23017_IO_setup_interrupt_pin();
    void MCP23017_IO_reset();
    uint8_t resolve_register(uint8_t base, uint8_t pin = 0);

};

#endif