# Project-Shadow-Flight
"Oh yee space fairer!
I will write your name on the moon with my fingertips"
~ ESA, EIRSAT-mission

![Static Badge](https://img.shields.io/badge/size-1U-blue)
![Static Badge](https://img.shields.io/badge/status-development-green)
![Static Badge](https://img.shields.io/badge/software-FreeRTOS-orange)
![Static Badge](https://img.shields.io/badge/MCU-STM32-purple)


## Introduction
*Project-Shadow Flight* is a homemade 1U cubesat using FreeRTOS on STM32F104CCU6 OBC 
and COTS components. None of these components are rad-hard. All are locally available 
components. This project was motivated by the curiosity to learn about space systems, 
mission softwares and space hardware in general, and try to replicate, within 
a defined time-frame,  a simple yet fully functional cubesat that can be used 
for demo purposes or even better, through the available channels, be improved for launch! 

This cubesat is designed to operate in the Low Earth Orbit(LEO). 

### Mission statement
The primary mission for this cubesat is Earth Observation (EO). It will capture images over
a given area, depending on the received mission from ground station. These images are then
compressed, stored and transmitted back to ground when in the TRANSMIT_TO_GROUND state. No image processing is 
done on board the Cubesate so as to save battery power and processing power for other critical 
tasks. 

# System components 
## 1. On-Board Computer 
The onboard computer is designed around STM32F401CCU6 Chip. 
The OBC is made up of the following sub-systems:
- STM32F401CCU6 
- MEMORY AND Data storage
- Interboard Wired communication 
- Status LEDs
- Programming header
- Deployment switcheS
- Remove before flight mechanism
- Interfaces to Payload board
- Power monitoring system from EPS
- Brown-out detection circuit 
- Hardware watchdog timer 

The image below shows the memory and debug block diagram used on the OBC:
![](./user-docs/images/obc-block.jpg)


In addition, the sensor board is also equipped with an ISA connector to maintain the PC-104 standard used 
ffor cubesats. This will further aid in communication with other boards.

### Requirements 

## 2. Sensor Board 
### Requirements 
1. Measure temperature inside the satellite
2. Detect acceleration of the satellite 
3. Determine angular velocity of the satellite
4. Detemine GPS location of the satelite
5. Measure the magnetic field around the satelite
6. Determine the position of the satelite in relation to the sun
7. Send sensor data to the on-board computer(OBC)

The block diagram is shown below:

![](./user-docs/images/sensor-board.png)

### Sensors used 
Listed below are the sensors used on the sensor board of the cubesat:
- Temperature Sensor
- Accelerometer
- Gyroscope
- GPS
- Magnetometer
- Sun sensor

### Communication protocol for sensors 
|   | Sensor             | Protocol |
|---|--------------------|----------|
| 1 | Temperature Sensor | 1-wire   |
| 2 | Accelerometer      | I2C      |
| 3 | Gyroscope          | I2C      |
| 4 | GPS                | UART     |
| 5 | Magnetometer       | I2C      |
| 6 | Sun sensor         | ADC      |

### PC-104 BUS
This project used the PC 104 standard for communication bus implementation. 

Bigest advantages of this standard:
- Stackable
- Interoperable- you can remove boards and use in another design
- Functionality extension - easy to add functionality
- Compact 
- Rugged - can handle shock and vibration 

An ISA connector looks like below: 
![](./user-docs/images/pc104-pcb.jpeg)

The images below explain the stacking of the PCB boards *(credit: Diamond Systems)*
![](./user-docs/images/pc104-dwg-500.gif)

![](./user-docs/images/pc104stack.gif)

Further reference: [PC-104 standard reference](https://www.diamondsystems.com/pc104)

The adpater pin assignment document I use is listed here [shadow-flight-pc104bus](https://docs.google.com/spreadsheets/d/11hD9y9vYMRVWSRXsNhsD9LqnLeL-uE_WEjQZ-0ekRwc/edit?usp=sharing)

## 3. Attitude Determination and Control
This system is responsible for receiving attitude data from sensors and acting on it in realtime 
to control the attitude(orientation ) of the satellite.
This is mainly implemented in software as the diagram below depicts.

The signals produced are fed into ana actuator or tticde coontrol,

Data from the sensors is read, then passed to the ADCS algorithm.

## Related documents
A list of related documents realated to this pject are provided below. They include diagrams, schematics,
design source files, datasheets, 2D diagrams, 3D assembly diagrams, test information and logs etc.

## Relevent videos and resource materials 
1. https://youtu.be/5voQfQOTem8 (Build your own satelite)
2. 

## Contribution and support
This project is not funded by any organization or entity and 
is solely reliant on out-of-pocket funding. 
We therefore heed to anyone desiring to contribute, 
in monetary form, technical advise, links and connections, 
electronic components etc., or even if you are interested in knowing more 
about the project details,
 you can reach out to us via this email (emwiti658@gmail.com) 
 and we will get back to you soonest.  

 Thank you again for your consideration! Ad Astra!

