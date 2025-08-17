"""
@author Edwin Mwiti
@brief This file helps experiment with different voltage divider values for 
DC voltage measurement circuit
"""

def calculate_output_voltage(vin, r1, r2):

    vo = (r2 / (r1 +r2 )) * vin
    print(f"VIN: {vin}, R1: {r1}, R2: {r2}: VO: {vo} ")
    return vo

calculate_output_voltage(12.2, 100000, 30000)