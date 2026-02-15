"""
This code runs the test engine for project shadow flight firmware
Used to test different subsystems of the cubesat
@author: Edwin M.
"""

import os
import json
from time import sleep
import wiringpi
from wiringpi import GPIO
import threading
from logger.std_logger import Logger

wiringpi.wiringPiSetup()

# command lengths
IMMEDIATE_CMD_LENGTH = 2
SCHEDULED_CMD_LENGTH = 3
SCHEDULED_WITH_PARAMETER_LENGTH = 4


class CommandEngineTester:

    def __init__(self, command_list_file, json_commands_file):
        self.logger = Logger()
        self.logger.print_log(
            "===================Command Engine Tester initialized==================="
        )

        self.led_pin = 2
        self.init_debug_hardware()

        self.cmd_filename = command_list_file
        self.json_commands_filename = json_commands_file

        self.command_list = []
        self.command_tokens = []

        self.json_cmd = ""
        self.json_file_object_list = []
        self.json_file_object_json = ""

        # parse the command list file
        self.parse_command_list_file()

    def init_debug_hardware(self):
        """Initialize debug GPIO"""
        wiringpi.pinMode(self.led_pin, GPIO.OUTPUT)
        wiringpi.digitalWrite(self.led_pin, GPIO.LOW)

    def parse_command_list_file(self):
        """
        Take a command list txt file and convert commands to JSON.
        If 2 tokens -> immediate command
        If 3 tokens -> scheduled command
        If 4 tokens -> scheduled command with parameter
        """

        self.show_activity()
        self.logger.print_log("Parsing commands from raw list to json_list...")

        if not os.path.exists(self.cmd_filename):
            self.logger.print_log("Path does not exist")
            return

        with open(self.cmd_filename) as command_file:
            for line in command_file:
                line = line.strip()
                cmd_token_list = line.split(" ")
                self.command_tokens.append(cmd_token_list)

        # save the JSON commands to file
        with open(self.json_commands_filename, "w") as json_file:
           
            self.logger.print_log("Writing commands to JSON file...")
            for tok_list in self.command_tokens:
                length = len(tok_list)

                # 2 tokens represent an immediate command
                if length == IMMEDIATE_CMD_LENGTH:
                    tpe = "immediate"

                # 3 tokens represent a scheduled command
                elif length == SCHEDULED_CMD_LENGTH:
                    tpe = "scheduled"

                # 4 tokens represent a scheduled command with a parameter
                elif length == SCHEDULED_WITH_PARAMETER_LENGTH:
                    tpe = "scheduled_param"

                else:
                    tpe = "invalid"

                self.cmd = {
                    "type": tpe,
                    "command": " ".join(tok_list)
                }

                self.json_cmd = json.dumps(self.cmd)

                #print(self.json_cmd)

                self.json_file_object_list.append(self.json_cmd)

                # output the commands to a json file with newline appended
                
                json_file.write(self.json_cmd + "\n")
        self.logger.print_log("Finished writing JSON to file")

        # test if the commands were written to file correctly
        self.dump_json_output_file()

    def show_activity(self):
        """Blink LED to show UART sending commands connected"""

        def blink():
            wiringpi.digitalWrite(self.led_pin, GPIO.HIGH)
            sleep(1)
            wiringpi.digitalWrite(self.led_pin, GPIO.LOW)

        threading.Thread(target=blink, daemon=True).start()

    def send_to_serial(self):
        """Send JSON file to serial"""
        pass

    def dump_json_output_file(self):
        """Test if the JSON output file was written correctly"""
        self.logger.print_log("Confirming JSON commands file contents...")
        with open(self.json_commands_filename, "r") as file:
            for line in file:
                print(line.strip())
        self.logger.print_log("\nEnd of JSON commands dump")


class OBCTest:
    def __init__(self):
        pass


if __name__ == "__main__":
    command_list_file = "command_list.txt"
    json_commands_file = "json_test_commands.txt"

    command_engine_instance = CommandEngineTester(
        command_list_file,
        json_commands_file
    )
