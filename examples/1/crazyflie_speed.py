# @file: crazyflie_speed.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
# Example for the ARGoS-Crazyflie Speed Actuator and Positioning Sensor
import libpy_controller_interface as argos_lib
import math

########################################################
#################### INITIALIZATION ####################
########################################################

def init():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("crazyflie flight initialized!")

########################################################
##################### CONTROL STEP #####################
########################################################

def controlstep():
    global counter
    log_position_and_orientation()
    speedActuatorTest()  # Activate speed testing
    counter += 1

########################################################
#################### SPEED ACTUATOR ####################
########################################################

# Speed Actuator Test: Handles the testing of speed actuators for quadrotors.
def speedActuatorTest():
    global counter, startFlag
    if startFlag:
        print_start_message("Quadrotor Speed Actuator")
    handle_speed_actuation()

def handle_speed_actuation():
    if counter >= 180:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0.0))
    elif counter >= 140:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(-0.85,-0.5,-0.1))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(-math.pi/2))
    elif counter >= 120:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0.0))
    elif counter >= 100:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.33,-0.5,-0.33))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(math.pi/2))
    elif counter >= 80:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0.0))
    elif counter >= 60:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(1.0,0.5,0.5))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(-math.pi/6))
    elif counter >= 40:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0.0))
    elif counter >= 20:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(-1.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(math.pi/6))

########################################################
################### UTILITY FUNCTIONS ##################
########################################################

def print_start_message(actuator_type):
    global startFlag
    print("===========================================")
    print(f"Crazyflie Test for {actuator_type}")
    print("===========================================")
    startFlag = False
    
def log_position_and_orientation():
    position = robot.position.get_position()
    orientation = robot.position.get_orientation()
    print(f"Position: {position}, Orientation: {orientation}")

########################################################
################### RESET AND DESTROY ##################
########################################################
def reset():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("Simulation reset")

def destroy():
    robot.logprint("Simulation ended")