# Project-Shadow-Flight
Oh yee space fairer!
I will write your name on the moon with my fingertips.
~ ESA, EIRSAT-mission

A homemade nanosat using RTEMS RTOS

# On-Board Computer 

# Sensor Board 
## Requirements 
1. Measure temperature inside the satellite
2. Detect attitude of the satellite 
3. Determine position of the satellite
4. Determine voltage and current values of satellite

### Sensors used 
- Solar Sensor - determine the incident direction of the sunlight
- Magnetometer - measure geomagnetism 
- Temperature Sensor
- Voltage Sensor
- Current Sensor
- Gyro sensor 
- Accelerometer 
- GPS sensor

### Communication protocol for sensors 
|Sensor|Protocol|
|--|--|
|Solar sensor||
|Magnetometer||
|Temperature Sensor||
|Voltage Sensor||
|Current Sensor||
|Gyroscope & Accelerometer|I2C|
|GPS|UART|

# Attitude Determination and Control
This system is responsible for receiving attitude data from sensors and acting on it in realtime 
to control the attitude(orientation ) of the satellite.
This is mainly implemented in software as the diagram below depicts.

The signals produced are fed into ana actuator or tticde coontrol,

Data from the sensors is read, then passed to the ADCS algorithm.
;

## Related documents
A list of related documents realated to this pject are provided below. They include diagrams, schematics,
design source files, datasheets, 2D diagrams, 3D assembly diagrams, test information and logs etc.

