# @file: crazyflie_led.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
# Example for the ARGoS-Crazyflie Led Actuator
import libpy_controller_interface as argos_lib
import math

########################################################
#################### INITIALIZATION ####################
########################################################

def init():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("crazyflie led initialized!")

########################################################
##################### CONTROL STEP #####################
########################################################

def controlstep():
    global counter
    ledActuatorTest()  # Led actuator testing
    counter += 1

########################################################
###################### LED ACTUATOR ####################
########################################################

# Position Actuator Test: Manages position actuator testing for quadrotors.
def ledActuatorTest():
    global counter, startFlag
    if startFlag:
        print_start_message("Led Actuator")
    handle_led_actuation(counter)

def handle_led_actuation(counter):
    if counter >= 120:
        robot.leds.set_all_colors("white")
        robot.logprint("LED Color: white")
    elif counter >= 100:
        robot.leds.set_all_colors("blue")
        robot.logprint("LED Color: blue")
    elif counter >= 80:
        robot.leds.set_all_colors("green")
        robot.logprint("LED Color: green")
    elif counter >= 60:
        robot.leds.set_all_colors("yellow")
        robot.logprint("LED Color: yellow")
    elif counter >= 40:
        robot.leds.set_all_colors("magenta")
        robot.logprint("LED Color: magenta")
    elif counter >= 20:
        robot.leds.set_all_colors("cyan")
        robot.logprint("LED Color: cyan")
    else:
        robot.leds.set_all_colors("black")
        robot.logprint("LED Color: black")

        
########################################################
################### UTILITY FUNCTIONS ##################
########################################################

def print_start_message(actuator_type):
    global startFlag
    print("===========================================")
    print(f"Crazyflie Test for {actuator_type}")
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
    robot.logprint("Simulation ended")