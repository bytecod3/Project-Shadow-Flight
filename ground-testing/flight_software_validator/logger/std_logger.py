"""
This file creates an stdout logger for serial debugging for this python code
@author: Edwin Mwiti
"""

import datetime

class Logger:
    """represents a logger object to use for debugging """

    def __init__(self):
        pass


    def print_log(self, msg):
        """log message on serial console with the timestamp it was created"""
        tstamp = datetime.strftime("%Y-%m-%dT%H:%M:%S")
        if len(msg) is 0:
            print(f"{tstamp} NULL msg")
        else:
            print(f"{tstamp} {msg}")
