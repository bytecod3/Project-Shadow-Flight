import wiringpi
import sys
import argparse


# using default SERIAL5 
#on linus the serial is ttyAS5
parser = argparse.ArgumentParser(description='')
parser.add_argument("--device", type=str, default="/dev/ttyAS5", help='specify the serial node')
args = parser.parse_args()

wiringpi.wiringPiSetup()
serial = wiringpi.serialOpen(args.device, 115200)
if serial < 0:
    print("Unable to open serial device: %s"% args.device)
    sys.exit(-1)
    
try:
  while True:
    wiringpi.serialPuts(serial, "Hello from orange pi\r\n");
    wiringpi.delayMicroseconds(300000)
  
except KeyboardInterrupt:
    print("\nexit")
    sys.exit(0)

wiringpi.serialClose(serial)  # Pass in ID
