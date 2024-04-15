# @file: crazyflie_battery.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
# Example for the ARGoS-Crazyflie Battery Sensor
import sys 

########################################################
#################### INITIALIZATION ####################
########################################################

def init():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("crazyflie battery initialized!")

########################################################
##################### CONTROL STEP #####################
########################################################

def controlstep():
    global counter
    if batterySensorTest(): 
        sys.exit()  # Exit the simulation if battery is depleted
    counter += 1

########################################################
##################### BATTERY SENSOR ###################
########################################################

# Position Actuator Test: Manages position actuator testing for quadrotors.
def batterySensorTest():
    global counter, startFlag, charge

    charge, time_remaining = robot.crazyflie_battery.get_reading()
    if startFlag:
        print_start_message("Battery Sensor")

    robot.logprint(f"Available Charge (%): {100*charge:.2f}")
    robot.logprint(f"Time Left (s): {time_remaining:.2f}")

    if charge <= 0 and time_remaining <= 0:
        print("Battery depleted. Terminating simulation.")
        robot.logprint("Battery depleted. Simulation ended.")
        return True  # Return True to indicate the simulation should terminate

    return False  # Return False to continue the simulation

########################################################
################### UTILITY FUNCTIONS ##################
########################################################

def print_start_message(sensor_type):
    global startFlag
    print("===========================================")
    print(f"Crazyflie Test for {sensor_type}")
    print("===========================================")
    startFlag = False

########################################################
################### RESET AND DESTROY ##################
########################################################
def reset():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("Simulation reset")

def destroy():
    robot.logprint(f"Last Recorded Battery Charge (%): {100*charge:.2f}")
    robot.logprint("Simulation ended")