#include <Arduino.h>
#include <Wire.h>

#define DEVICE_ADDRESS 0x53

#define DEV_ID_REG 0x00
#define POWER_CTL 0x2D
#define BW_RATE 0x2c
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

void init_adxl(){
    // set up the POWER_CTL register to measurement mode 
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(POWER_CTL);
    Wire.write(0x08); // measurement mode 
    Wire.endTransmission(true); // no restart

    // set the BW ODT and data rate 
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(BW_RATE);
    Wire.write(0x08); // 25Hz data rate, 12.5 LPF Bandwidth
    Wire.endTransmission(true);
}

void read_acceleration() {
    int16_t acc_x, acc_y, acc_z = 0;

    // read x
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(DATAX0);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, 2);
    acc_x = (Wire.read() << 8 ) | (Wire.read());

    // read y
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(DATAY0);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, 2);
    acc_y = (Wire.read() << 8 ) | (Wire.read());
    
    // read z
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(DATAZ0);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, 2);
    acc_z = (Wire.read() << 8 ) | (Wire.read());

    // convert to float values 
    float x = 0.000061035f * 9.81 * acc_x;
    float y = 0.000061035f * 9.81 * acc_y;
    float z = 0.000061035f * 9.81 * acc_z;

    acceleration_packet.x = x;
    acceleration_packet.y = y;
    acceleration_packet.z = z;

}

void setup() {
    Serial.begin(115200);
    delay(20);

    Wire.begin(21, 22);

    // read device ID 
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(DEV_ID_REG);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDRESS, 1);
    uint8_t device_id = Wire.read();

    Serial.print("Device ID: "); Serial.println(device_id, HEX);

    Serial.println("Initializing ADXL...");
    init_adxl();

}

void loop() {
    static unsigned long last_millis;
    if(millis() - last_millis > 200) {
        read_acceleration();

        Serial.print("x: "); Serial.print(acceleration_packet.x); Serial.print("\t\t");
        Serial.print("y: "); Serial.print(acceleration_packet.y); Serial.print("\t\t");
        Serial.print("z: "); Serial.print(acceleration_packet.z); Serial.print("\t\t");
        Serial.println();

        last_millis = millis();
    }

}