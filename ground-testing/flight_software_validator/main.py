"""
 This code runs the test engine for project shadow flight firmware
 Used to test different subystems if the cubesat
 @author: Edwin M.
"""
import os
from logger.std_logger import Logger



class CommandEngineTester:
    def __init__(self, command_list_file):
        Logger.print_log("Command Engine Tester initialized")
        self.cmd_filename = command_list_file
        self.parse_command_list_file()
        self.command_list = []

    def parse_command_list_file(self):
        """Take a command list txt file and convert commands to JSON """
        if not os.path.exists(self.cmd_filename):
            Logger.print_log("Path does not exist")
        else:
            command_file = open(self.cmd_filename)
            for line in command_file.readlines():
              Logger.print_log(line)       
        

class OBCTest:
    def __init__():
        pass


if __name__=="__main__":
    command_list_file = "command_list.txt"
    command_engine_instance = CommandEngineTester(command_list_file)
    
    
