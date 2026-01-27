### Applications on the flight software

THe table below shows the application softwares that are developed within the flight software(FSW) to facilitate various actions on in the FSW.  

| Application name         | Function                |
|-------------|----------------------|
| FileTransferApp | Transfer/Receiver files to/from ground         |
| ChecksumApp | Data integrity checking of memory/tables and files        |
| CommandSequencerApp | Accept CCSDS telecommand packets over IP/UDP port        |
| DataStorageApp | Records housekeeping, engineering and sensor data onboard for downlink | 
| FileManagerApp | Interfaces to the ground for managing files |
| HousekeepingApp | Collects and repackages telemetry from other applications |
| HealthCheckerApp | Ensures critical tasks check in, services wathcdogs, detects CPU hogging, and calculates CPU utilization |
| LimitCheckerApp | Provides the capability to monitor values and take action when exceeded threshold |
| MemoryProbeApp | Allows ground to check contents of specific memory locations, for debugging |
| MemoryManagerApp | Provides ability to load and dump memory |
| OnboardSchedulerApp | Simple activity scheduler with one second resolution |
| TelemetryOutputApp | Sends CCSDS telemetry packets over UDP/IP port |
| SnapCaptureApp | For controlling the onboard camera payload snap capture times |


### Inter-task Software Communication bus 
This is a queue management layer that ensures maximum efficient communication between all the tasks that need/may need any type of data from the fligth software

#### Design diagram

### ShadowFlight Executive Operator 



#### Scratchpad
shared -> (debuguart)
shared -> (command processor queue) -> can be read and written at the same time. We want to avoid this -> check semaphore


//============= PYTHON SCRIPT PSEUDO CODE ===================

JSON command
{
    "type":"immediate",
    "command":"EPS RESTART"
}


Create Serial connection 

// On success
Open Serial 
Open the list of commands (EPS RESTART, COMMS RESET etc)

// for each command convert the list of commands into the above JSON structure -> add timestamp
// write into a clean new json commands file

once the run test button is pressed, for each of the json strings, write to serial

// debug the response on test PC, response of commands can be logged to file 



