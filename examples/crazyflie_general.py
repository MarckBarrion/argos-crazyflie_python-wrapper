# @file: crazyflie_general.py

# @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>

# An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)

# Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)

# Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)

#!/usr/bin/env python3
# Test for Crazyflie ARGoS-Python Wrapper
import libpy_controller_interface as argos_lib
import math

########################################################
#################### INITIALIZATION ####################
########################################################

# Initialization: Defines the starting conditions and initial setup for the Crazyflie simulation.
def init():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("crazyflie test flight initialized!")
    set_led_color("red")

########################################################
##################### CONTROL STEP #####################
########################################################

# Control Step: Main loop handling the control logic for each simulation step.
def controlstep():
    global counter
    log_position_and_orientation()
    # speedActuatorTest()  # Activate speed testing
    positionActuatorTest()  # Activate position testing
    batterySensing()
    proximitySensing()
    counter += 1

########################################################
################## PROXIMITY SENSING ###################
########################################################

# Proximity Sensing: Logs proximity sensor data.
def proximitySensing():
    proximity_read = robot.crazyflie_proximity.get_readings()[0]
    print(f"Proximity Sensor 0: {proximity_read}")

########################################################
################ BATTERY LEVEL SENSING #################
########################################################

# Battery Sensing: Monitors and logs battery status.
def batterySensing():
    charge, time_remaining = robot.crazyflie_battery.get_reading()
    log_battery_status(charge * 100, time_remaining)

########################################################
#################### SPEED ACTUATOR ####################
########################################################

# Speed Actuator Test: Handles the testing of speed actuators for quadrotors.
def speedActuatorTest():
    global counter, startFlag
    if startFlag:
        print_start_message("Quadrotor Speed Actuator")
    handle_speed_actuation()

########################################################
################### POSITION ACTUATOR ##################
########################################################

# Position Actuator Test: Manages position actuator testing for quadrotors.
def positionActuatorTest():
    global counter, startFlag
    if startFlag:
        print_start_message("Quadrotor Position Actuator")
    handle_position_actuation()

########################################################
################ SPEED ACTUATOR HANDLE ##############$##
########################################################

def handle_speed_actuation():
    if counter >= 110:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0))
        set_led_color("white")
    elif counter >= 100:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.4, 0.4, 0.4))
        set_led_color("green")
    elif counter >= 80:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(-0.4, -0.4, -0.4))
    elif counter >= 60:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.4))
    elif counter >= 40:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.4, 0.0))
        set_led_color("blue")
    elif counter >= 20:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.4, 0.0, 0.0))
        robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(math.pi))
    elif counter >= 0:
        robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))

########################################################
################### POSITION ACTUATOR ##################
########################################################
def handle_position_actuation():
    if counter >= 110:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.0, 0.0, 0.0))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0))
        set_led_color("white")
    elif counter >= 100:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(-0.5, -0.5, 0.1))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi))
        set_led_color("green")
    elif counter >= 80:
        robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.5, 0.5, 0.1))
        robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi))
    elif counter >= 60:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0, 0.0, 0.2))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0))
    elif counter >= 40:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(-1.0, -1.0, 0.5))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(-math.pi))
        set_led_color("blue")
    elif counter >= 20:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(1.0, 1.0, 0.5))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(math.pi))
    elif counter >= 0:
        robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0, 0.0, 0.5))
        robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0))

########################################################
################### UTILITY FUNCTIONS ##################
########################################################

def set_led_color(color):
    robot.leds.set_all_colors(color)

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

def log_battery_status(charge, time_remaining):
    if counter % 5 == 0:
        robot.logprint(f"Available Charge (%): {charge:.2f}")
        robot.logprint(f"Time Left (s): {time_remaining:.2f}")

########################################################
################### RESET AND DESTROY ##################
########################################################
# Reset and Destroy: Handle simulation reset and cleanup.
def reset():
    global counter, startFlag
    counter, startFlag = 0, True
    robot.logprint("Simulation reset")

def destroy():
    robot.logprint("Simulation ended")
