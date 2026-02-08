"""
 This code runs the test engine for project shadow flight firmware
 Used to test different subystems if the cubesat
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
#wiringpi.pinMode(2, GPIO.OUTPUT)
#wiringpi.digitalWrite(2,GPIO.HIGH)

# command lengths 
IMMEDIATE_CMD_LENGTH = 2
SCHEDULED_CMD_LENGTH = 3
SCHEDULED_WITH_PARAMETER_LENGTH = 4

class CommandEngineTester:
    def __init__(self, command_list_file):
        self.logger = Logger()
        self.logger.print_log("===================Command Engine Tester initialized===================")
        
        self.led_pin = 2
        self.init_debug_hardware()
        
        self.cmd_filename = command_list_file
        self.command_list = []
        self.command_tokens = []   
        
        self.json_cmd = ""
        
        self.json_file_object_list = []
        self.json_file_object_json = ""
        
        """ parse the command list file """
        self.parse_command_list_file()
        
    def init_debug_hardware(self):
      """initilize debug GPIO"""
      wiringpi.pinMode(self.led_pin, GPIO.OUTPUT)
      wiringpi.digitalWrite(self.led_pin, GPIO.LOW)
      pass
      
               
    def parse_command_list_file(self):
        """Take a command list txt file and convert commands to JSON/ count the number of strings in the line, 
        if 2->immediate command, if 3->scheduled command, if 4->scheduled command with parameter     
        create a JSON command fomr this. See Firmware commmand structure
        todo: handle immediate command with parameters
        """
        
        self.show_activity()
        
        if not os.path.exists(self.cmd_filename):
            self.print_log("Path does not exist")
        else:
            command_file = open(self.cmd_filename)
            
            line_count = 0 
            for line_count, line in enumerate(command_file.readlines()):
            
              # remove the trailing \n character
              line = line[:-1]
              cmd_token_list = line.split(" ")
              
              self.command_tokens.append(cmd_token_list)
                
            for tok_list in self.command_tokens:
              length = len(tok_list)
              
              """ 2 tokens represent an immediate command"""
              if length == IMMEDIATE_CMD_LENGTH:
                # compose the command
                tpe = "immediate"       
              
              #""" 3 tokens represent a scheduled command """
              elif length == SCHEDULED_CMD_LENGTH:
                tpe = "scheduled"

              #"""4 tokens represent a scheduled command with a parameter"""
              elif length == SCHEDULED_WITH_PARAMETER_LENGTH:
                tpe = "scheduled_param"
                   
              else:
                tpe = "invalid"
                
              self.cmd = {"type":tpe, "command":" ".join(tok_list)}

              # convert to JSON
              self.json_cmd = json.dumps(self.cmd)
              print(self.json_cmd)
              
              #self.json_file_object_list.append(self.json_cmd)
              
    def show_activity(self):
      """blink LED to show UART sending commands connected"""
      #while there is data being transmitted over serial, blink 
      # todo: use a UART RX/TX flag here
      def blink():
        wiringpi.digitalWrite(self.led_pin, GPIO.HIGH)
        sleep(1)
        wiringpi.digitalWrite(self.led_pin, GPIO.LOW)
        
      threading.Thread(target=blink, daemon=True).start()
      
    def send_to_serial(self):
      """send json file to serial"""
      pass
      
    
class OBCTest:
    def __init__():
        pass


if __name__=="__main__":
    command_list_file = "command_list.txt"
    command_engine_instance = CommandEngineTester(command_list_file)
    
    
