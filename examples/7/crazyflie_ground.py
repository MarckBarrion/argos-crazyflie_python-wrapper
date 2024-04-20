# @file: crazyflie_ground.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
import libpy_controller_interface as argos_lib
import math
import random

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
    # log_position_and_orientation()
    positionActuatorRuns()  
    groundSensing() 
    counter += 1

########################################################
#################### GROUND SENSING ####################
########################################################

def groundSensing():
    readings = robot.crazyflie_ground.get_readings()
    print("Ground Sensor Readings: ", readings)

########################################################
################### POSITION ACTUATOR ##################
########################################################

def positionActuatorRuns():
    global counter, startFlag
    if startFlag:
        print_start_message("Crazyflie Ground Sensor")
    handle_position_actuation()

def handle_position_actuation():
    if counter >= 180:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0))
    # elif counter >= 140:
    #     robot.quadrotor_position.set_relative_position(argos_lib.vector3(-0.85,-0.5,-0.1))
    #     robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi/3))
    # elif counter >= 120:
    #     robot.quadrotor_position.set_relative_position(argos_lib.vector3(-1.0,0.5,0.1))
    #     robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi/2))
    # elif counter >= 100:
    #     robot.quadrotor_position.set_relative_position(argos_lib.vector3(-2.0,0.0,0.0))
    #     robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0.0))
    elif counter >= 200:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(2.0,1.0,0.1))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0.0))
    elif counter >= 120:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(-2.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))
    elif counter >= 50:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(2.0,1.0,0.1))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0.0))
    elif counter >= 20:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(-2.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))

########################################################
################### UTILITY FUNCTIONS ##################
########################################################

def print_start_message(sensor_type):
    global startFlag
    print("===========================================")
    print(f"Crazyflie Test for {sensor_type}")
    print("===========================================")
    startFlag = False

def log_position_and_orientation():
    position = robot.position.get_position()
    orientation = robot.position.get_orientation()
    # Assuming position is a list [x, y, z] and orientation is a float
    print(f"Position: [{position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f}], Orientation: {orientation:.2f}")


########################################################
################### RESET AND DESTROY ##################
########################################################

def reset():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("Simulation reset")

def destroy():
    robot.logprint("Simulation ended")
