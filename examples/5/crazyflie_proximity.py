# @file: crazyflie_proximity.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
# Example for the ARGoS-Crazyflie Proximity Sensor
import libpy_controller_interface as argos_lib
import math

########################################################
#################### INITIALIZATION ####################
########################################################

def init():
    global counter, maxReadIndex, startFlag
    counter, maxReadIndex, startFlag = 0, 0, True
    robot.logprint("crazyflie flight initialized!")

########################################################
##################### CONTROL STEP #####################
########################################################

def controlstep():
    global counter
    positionActuatorRuns()  
    proximitySensing() # Activate proximity sensor testing
    counter += 1

########################################################
################## PROXIMITY SENSING ###################
########################################################

# Proximity Sensing: Logs proximity sensor data.
def proximitySensing():
    # Get readings from all proximity sensors
    readings = robot.crazyflie_proximity.get_readings()

    # Set a threshold below which an obstacle is considered detected and above which valid readings are considered
    threshold = 30  # Threshold for detecting obstacles
    noise_floor = 0.1  # Minimum valid sensor reading to consider (adjust based on your sensor's behavior)

    # Check pairs of sensors for each direction
    front_obstacle = readings[0] > noise_floor and readings[7] > noise_floor and (readings[0] < threshold or readings[7] < threshold)
    back_obstacle = readings[3] > noise_floor and readings[4] > noise_floor and (readings[3] < threshold or readings[4] < threshold)
    left_obstacle = readings[1] > noise_floor and readings[2] > noise_floor and (readings[1] < threshold or readings[2] < threshold)
    right_obstacle = readings[5] > noise_floor and readings[6] > noise_floor and (readings[5] < threshold or readings[6] < threshold)

    # Log details of the detection
    if front_obstacle:
        robot.logprint(f"Obstacle detected in front. Sensor values: Front-Left={readings[0]}, Front-Right={readings[7]}")
    if back_obstacle:
        robot.logprint(f"Obstacle detected at the back. Sensor values: Back-Left={readings[3]}, Back-Right={readings[4]}")
    if left_obstacle:
        robot.logprint(f"Obstacle detected on the left. Sensor values: Left-Front={readings[1]}, Left-Back={readings[2]}")
    if right_obstacle:
        robot.logprint(f"Obstacle detected on the right. Sensor values: Right-Back={readings[5]}, Right-Front={readings[6]}")

    # If no paired sensors detect an obstacle, check individual sensors
    if not (front_obstacle or back_obstacle or left_obstacle or right_obstacle):
        for index, reading in enumerate(readings):
            if reading > noise_floor and reading < threshold:
                sensor_positions = {
                    0: 'Front-Left',
                    1: 'Left-Front',
                    2: 'Left-Back',
                    3: 'Back-Left',
                    4: 'Back-Right',
                    5: 'Right-Back',
                    6: 'Right-Front',
                    7: 'Front-Right'
                }
                robot.logprint(f"Obstacle detected by {sensor_positions[index]} sensor with value: {reading}")

########################################################
################### POSITION ACTUATOR ##################
########################################################

# Position Actuator Test: Manages position actuator testing for quadrotors.
def positionActuatorRuns():
    global counter, startFlag
    if startFlag:
        print_start_message("Quadrotor Position Actuator")
    handle_position_actuation()

def handle_position_actuation():
    if counter >= 370:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi))
    elif counter >= 310:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(1.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(math.pi/2))
    elif counter >= 280:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(math.pi/3))
    elif counter >= 180:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0,0.7,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))
    elif counter >= 110:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))
    elif counter >= 45:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(-1.0,0.0,0.2))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))
    elif counter >= 35:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.0,0.0,0.0))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0.0))
    elif counter >= 5:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(1.0,0.0,0.0))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0.0))

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
    robot.logprint("Simulation ended")