"""
This file creates an stdout logger for serial debugging for this python code
@author: Edwin Mwiti
"""

import datetime

class Logger:
    """represents a logger object to use for debugging """

    def __init__(self):
        self.msg = "NULL"


    def print_log(self, msg):
        """log message on serial console with the timestamp it was created"""
        tstamp = datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S")
        self.msg = msg
        if len(msg) == 0:
            print(f"{tstamp} NULL")
        else:
            print(f"{tstamp} {msg}")
            
def main():
  logger = Logger()

if __name__ == "__main__":
  main()
  