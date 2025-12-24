#include <Arduino.h>
#include <Wire.h>

#define DEVICE_ADDRESS 0x53

#define DEV_ID_REG 0x00
#define POWER_CTL 0x2D
#define BW_RATE 0x2c
#define DATA_FORMAT     0x31		/*!< dat format control */
#define DATAX0 			0x32		/*!< x axis data 0 */
#define DATAX1 			0x33		/*!< x axis data 1 */
#define DATAY0 			0x34		/*!< y axis data 0 */
#define DATAY1 			0x35		/*!< y axis data 1 */
#define DATAZ0 			0x36		/*!< z axis data 0 */
#define DATAZ1 			0x37		/*!< z axis data 1 */

typedef struct {
    float x;
    float y;
    float z;
} acc_data_t;

acc_data_t acceleration_packet;

uint8_t read_register(uint8_t reg_addr) {
    uint8_t reg_data;
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(reg_addr);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, (uint8_t)1);
    
    reg_data = Wire.read();

    return reg_data;
}

void read_registers(uint8_t reg_addr, uint8_t* data_buffer, uint8_t length) {
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(reg_addr);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, length);
    
    // save to buffer 
    for(uint8_t i = 0; i < length; i++) {
        data_buffer[i] = Wire.read();
    }

}

void write_register(uint8_t reg_addr, uint8_t value) {
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(reg_addr);
    Wire.write(value);
    Wire.endTransmission(true);
}

void init_adxl(){
    // set the data format and full scale range 
    uint8_t format_reg_val = read_register(DATA_FORMAT);

    Serial.print("DEV_FORMAT Before: ");Serial.println(format_reg_val, HEX);

    // set range to 16g
    format_reg_val &= ~(0x0F); // clear range bits 
    format_reg_val |= 0x03; // 16g

    // write back 
    write_register(DATA_FORMAT, format_reg_val);

    uint8_t v = read_register(DATA_FORMAT);
    Serial.print("DEV_FORMAT After: ");Serial.println(v, HEX);

    write_register(POWER_CTL, 0x08); // measurement mode 
    write_register(BW_RATE, 0x08); // 25Hz data rate, 12.5 LPF Bandwidth

}

float convert_to_g(int16_t raw_value) {
    float scale_factor = 0.0312f;

    // todo: use a switch case for different ranges 
    return raw_value * scale_factor;
}

void read_acceleration(float& x, float& y, float& z) {
    uint8_t acc_x, acc_y, acc_z = 0;

    uint8_t data[6];
    read_registers(DATAX0, data, 6);

    // combine into signed 16-bit values 
    int16_t raw_x = (int16_t) ((data[1] << 8) | (data[0]));
    int16_t raw_y = (int16_t) ((data[3] << 8) | (data[2]));
    int16_t raw_z = (int16_t) ((data[5] << 8) | (data[4]));

    x = convert_to_g(raw_x);
    y = convert_to_g(raw_y);
    z = convert_to_g(raw_z);
    
}

void setup() {
    Serial.begin(115200);
    delay(20);

    Wire.begin(21, 22);

    // read device ID 
    uint8_t device_id = read_register(DEV_ID_REG);

    Serial.print("Device ID: "); Serial.println(device_id, HEX);
    Serial.println();

    Serial.println("Initializing ADXL...");
    init_adxl();

}

void loop() {
    static unsigned long last_millis;
    if(millis() - last_millis > 100) {
        read_acceleration(acceleration_packet.x, acceleration_packet.y, acceleration_packet.z);

        Serial.print("x: "); Serial.print(acceleration_packet.x); Serial.print("\t\t");
        Serial.print("y: "); Serial.print(acceleration_packet.y); Serial.print("\t\t");
        Serial.print("z: "); Serial.print(acceleration_packet.z); Serial.print("\t\t");
        Serial.println();

        last_millis = millis();
    }

}