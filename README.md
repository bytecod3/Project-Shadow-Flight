# Project-Shadow-Flight
"Oh yee space fairer!
I will write your name on the moon with my fingertips"
~ ESA, EIRSAT-mission

![Static Badge](https://img.shields.io/badge/size-1U-blue)
![Static Badge](https://img.shields.io/badge/status-development-green)
![Static Badge](https://img.shields.io/badge/software-FreeRTOS-orange)
![Static Badge](https://img.shields.io/badge/MCU-STM32-purple)

## Introduction
**Project-Shadow Flight** is a homemade 1U cubesat designed and built using FreeRTOS on STM32 framework 
and COTS components. None of these components are radiation hardened. 


### Design Videos for visual consumers
If you are more of a visual consumer, I have documented the whole design process in my Youtube channel playlist 
here: 
[Comprehensive Design videos](https://youtu.be/9HoKzI_bBjs?list=PLSQRKAY5h7mGCnkXsugdVSHa72dnC0zQU)


## Motivation
This project was motivated by the curiosity to learn about space systems, especially cubesats, 
mission softwares and space electronic hardware in general, and try to replicate, within 
a defined time-frame, a simple yet fully functional cubesat that can be used 
for demo purposes or even better, through the available channels, be improved for launch! 

## Mission statement
The primary mission for this cubesat is Earth Observation (EO). 
It is designed to operate in the Low Earth Orbit(LEO). It will capture images over
a given area, on a sun-synchronous subrecurrent orbit, depending on the received command from ground station. These images are then
compressed, stored and transmitted back to ground when a pass over a base station is reached. No image processing is 
done on board the Cubesate so as to save battery power and processing power for other critical tasks. 

The cubesat is designed to have two major operation modes:  
1. Normal operation mode
2. Mission operation mode 

These two states can be configured and changed accordingly from the ground station.

# System components 
A cubesat in general is made up of the following subsystems:  
1. Onboard Computer system (OBC)
2. Communication and Data Handling system (CD & H)
3. Electrical Power Supply system (EPS)
4. Attitude Determination and Control system (ADCS)
5. Sensor and Payload System 
6. Structural and Thermal system 

## 1. Onboard Computer 
### Introduction
The onboard computer performs the housekeeping tasks needed by the cubesat. It is the main link between all the other 
subsystems used in the cubesat.

### Functional requirements
The following is a list of the functional requirements of the OBC:

#### 1. The CubeSat shall perform reliable data processing and control operations using an STM32F401CCU6 microcontroller.
This includes handling telemetry, command execution, subsystem coordination, and real-time control tasks.

#### 2. The CubeSat shall store mission-critical data and logs in non-volatile memory to prevent data loss during power cycles.
Memory must support both temporary (RAM) and permanent (Flash or EEPROM) storage for payload data, telemetry, and system logs.

#### 3. The CubeSat shall support inter-board wired communication between the OBC, payload, and EPS using standard digital protocols (e.g., UART, I2C, SPI).
The interfaces must support command, telemetry, and sensor data exchange.

#### 4. The CubeSat shall indicate system and subsystem statuses using onboard status LEDs.
LED indicators shall reflect boot status, error conditions, power state, and communication activity for debugging and development.

#### 5. The CubeSat shall be programmable via an external programming/debugging header accessible during integration and testing.
This header must support SWD or UART-based flashing and debugging.

#### 6. The CubeSat shall utilize deployment and "Remove Before Flight" (RBF) switches to ensure safe handling and automatic activation post-deployment.
RBF switch shall disconnect power from the CubeSat until it is removed prior to launch. Deployment switches must detect separation from the deployer and initiate startup sequences.

#### 7. The CubeSat shall interface with the payload board via a standardized electrical connector to exchange power, control, and data signals.
This nterface must be robust to launch vibrations and support defined command/data protocols.

#### 8. The CubeSat shall monitor voltage and current levels of its power system using telemetry from the EPS.
Power monitoring shall allow detection of over/under-voltage and overcurrent events to protect hardware.

#### 9. The CubeSat shall implement a brown-out detection mechanism to safely handle unexpected power drops.
Upon voltage drop below a threshold, the MCU must reset safely or enter a low-power state to preserve system integrity.

#### 10. The CubeSat shall include a hardware watchdog timer to recover from software faults or unresponsive states.
The watchdog must be periodically refreshed by software; failure to do so shall cause a system reset.

#### 11. The CubeSat shall include up to 3 inhibit switches in accordance with CubeSat deployment standards to prevent premature activation of systems.
Inhibits must disable power or specific subsystems until conditions for deployment are met (e.g., separation from deployer).

### Components of the OBC
The OBC is made up of the following sub-systems:
- STM32F401CCU6 
- MEMORY AND Data storage
- Interboard Wired communication 
- Status LEDs
- Programming header
- Deployment switches
- Remove before flight switch
- Interfaces to Payload board
- Power monitoring system from EPS
- Brown-out detection circuit 
- Hardware watchdog timer 
- Inhibit switches 

The image below shows the memory and debug block diagram used on this cubesat's OBC:

<img src="images/obc-block.jpg" alt="Shadow flight OBC" width="500" height="700"/>
  

**To note, all the PCBs are equipped with ISA PC/104 connectors to make stacking possible**

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

![](user-docs/images/sensor-board.png)

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


## 4. Electrical Power System (EPS)
### Introduction
The EPS is responsible for the following functions:
    - Energy generation
    - Energy conversion
    - Power regulation
    - Power storage
    - Power distribution to loads

There are several methods to do power generation and other fucntions listed above. However, the recommended approach among most cubesat design teams, and the one I choose to follow for this project, is the procedure below:

    1. Define the power consumption and electrical characteristics of the spacecraft bus components 
    2. Define the necessary power generation and energy storage required 
    3. Select the power generation and energy storage methods 
    4. Analyse the system's power budget and profile based on the start to end of mission
    5. Design power conversion, management and distribution subsystem to interface the power sources 
    6. Procure and fabricate components 
    7. Conduct tests on isolated components 
    8. Conduct tests on integrated components 

There is a lot that can be discussed in respect to EPS but I have tried to be consise and to the point in the 
summaries below:

### a) Power consumption of different bus components 
### b) Power generation 
### c) Energy storage 
### d) Mission analysis in regards to power 
### e) EPS Schematics summary

#### Conversion
#### Power Distribution Schemes
#### Power supply control

### f) Isolated tests 
### g) EPS integration and Testing


## Related documents
A list of related documents realated to this pject are provided below. They include diagrams, schematics,
design source files, datasheets, 2D diagrams, 3D assembly diagrams, test information and logs etc.

## Relevent videos and resource materials 
1. https://youtu.be/5voQfQOTem8 (Build your own satelite)
2. https://pressbooks-dev.oer.hawaii.edu/epet302/chapter/5-4-design-process-and-drivers/
3. https://resources.altium.com/p/prototyping-solar-solution-your-outdoor-embedded-device
4. https://pycubed.org/What%20is%20PyCubed%20f257a98ec60044538d8fbdc20fec987f.html
5. https://github.com/hsfl/artemis-hardware
6. https://sites.google.com/hawaii.edu/artemiscubesatkit

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

