/**
 * @author Edwin Mwiti
 * @brief Creates structs to hold data types from cubesat boards
 * @date 28/12/25
 */

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>

/*===================================================== ADCS data */
typedef struct _adxl345_data {
    float x_acc;
    float y_acc;
    float z_acc;
} adxl345_data_t; // todo: this comes formatted from ADXL345 hardware driver

typedef struct _mpu6050_data {
    float x_acc;
    float y_acc;
    float z_acc;
    float x_ang;
    float y_ang;
    float z_ang;
} mpu6050_data_t; // todo: this comes foarmatted from MPU6050 hardware driver

typedef struct _magnetometer_data {
    float x_flux;
    float y_flux;
    float z_flux;
} magnetometer_data_t; // todo: comes from Magnetometer hardware driver

typedef struct _gps_data {
    float lon;
    float lat;
    float speed;
    float satellites;
    float course;
} gps_data_t; // todo: these are formatted from GPS hardware driver.

// has sun 1, sun 2, sun 3, sun 4 sensors 
typedef struct _ads1015_1_data {
    uint16_t sun1;
    uint16_t sun2;
    uint16_t sun3;
    uint16_t sun4;
} ads1015_1_data_t;

// has sun 5, sun 6
typedef struct _ads1015_2_data {
    uint16_t sun5;
    uint16_t sun6;
} ads1015_2_data_t;

typedef struct _adcs_data{
    adxl345_data_t adxl345_d;
    mpu6050_data_t mpu6050_d;
    magnetometer_data_t magnetometer_d;
    gps_data_t gps_d;
    ads1015_1_data_t sun_d1;
    ads1015_1_data_t sun_d2;

    float onboard_temperature; // operational data

} adcs_data_t;

/*================================================== COMMS board data */
typedef struct _comms_data{
    float t;
} comms_data_t;

/* EPS_DATA */

typedef struct _bq25703_data { // todo: comes from BQ25703 driver
    float adc_vsys;
    float adc_vbat;
} bq25703_data_t;

typedef struct _eps_data{
    float solar_voltage;            // solar power
    float solar_current;
    float solar_power;

    bq25703_data_t bq25703_d;       // BQ25703 data

    float reg_3v3_voltage;          // voltage regulators data
    float reg_3v3_current;
    float reg_5v_voltage;
    float reg_5v_current;
    float reg_vsys_voltage;
    float reg_vsys_current;

    float onboard_temperature_ds;   // operational data
    float onboard_temperature_ntc;
    uint8_t eps_board_detect;

    uint8_t deploy_1;              // deployment states
    uint8_t deploy_2;
    uint8_t rbf;
} eps_data_t;

/*======================================================== PAYLOAD data */
typedef struct _payload_data{

} payload_data_t;

/*========================================================= OBC data. nest all other data types */
typedef struct _obc_data{   
    comms_data_t comms_d;
    eps_data_t eps_d;
    payload_data_t payload_d;

     float onboard_temperature; // operational data
} obc_data_t;



#endif