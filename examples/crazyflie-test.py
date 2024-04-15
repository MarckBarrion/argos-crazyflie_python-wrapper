# @file: crazyflie-test.py

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
# Variable Declaration
counter = 0
startFlag = True
position = []
batteryInformation = []
availableCharge = 0
timeLeft =0

def init():
    global counter, startFlag
    counter = 0
    startFlag = True
    # Log to ARGoS GUI
    robot.logprint("crazyflie test flight!")
    # Set initial color of LED to red
    robot.leds.set_all_colors("red")

########################################################
##################### CONTROL STEP #####################
########################################################

def controlstep():
    global counter
    # Logging values to console:
    position = robot.position.get_position()
    orientation = robot.position.get_orientation()
    print("Position: ", position)
    print("Orientation: ", orientation)

    # Use if actuator is quadrotor_speed
    # speedActuatorTest()
    # Use if actuator is quadrotor_speed
    positionActuatorTest()

    # Battery Sensor
    batterySensing()

    # Battery Sensor
    proximitySensing()

    # Increment simulation counter
    counter += 1

########################################################
############### PROXIMITY SENSOR LOGGING ###############
########################################################
def proximitySensing():
    readingProx = robot.crazyflie_proximity.get_readings()[0]
    print("Proximity Sensor 0: ", readingProx)

########################################################
################ BATTERY SENSOR LOGGING ################
########################################################
def batterySensing():
    batteryInformation = robot.crazyflie_battery.get_reading()
    availableCharge = 100*batteryInformation[0]
    timeLeft = batteryInformation[1]

    # Logging values to console periodically:
    if counter % 5 == 0:
        robot.logprint("Available Charge (%): {:.3f}".format(availableCharge))  # 2 decimal places
        robot.logprint("Time Left: {:.3f}".format(timeLeft))                # 2 decimal places


#############################################s###########
############## TEST FOR QUADROTOR_SPEED ################
########################################################
## Note: Use if actuator is quadrotor_speed

def speedActuatorTest():
    global counter, startFlag
    if startFlag:
        print("===========================================")
        print("Crazyflie Test for Quadrotor Speed Actuator")
        print("===========================================")
        startFlag = False
    else:
        if counter >= 110:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
            robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(0))
            # Set color of LED to white
            robot.leds.set_all_colors("white")
        elif counter >= 100:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.4, 0.4, 0.4))
            # Set color of LED to green
            robot.leds.set_all_colors("green")
        elif counter >= 80:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(-0.4, -0.4, -0.4))
        elif counter >= 60:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.4))
        elif counter >= 40:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.4, 0.0))
            # Set color of LED to blue
            robot.leds.set_all_colors("blue")
        elif counter >= 20:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.4, 0.0, 0.0))
            robot.quadrotor_speed.set_rotational_velocity(argos_lib.radians(math.pi))
        elif counter >= 0:
            robot.quadrotor_speed.set_linear_velocity(argos_lib.vector3(0.0, 0.0, 0.0))
        counter += 1


########################################################
############# TEST FOR QUADROTOR_POSITION ##############
########################################################
## Note: Use if actuator is quadrotor_position
def positionActuatorTest():
    global counter, startFlag
    if startFlag:
        print("==============================================")
        print("Crazyflie Test for Quadrotor Position Actuator")
        print("==============================================")
        startFlag = False
    else:
        if counter >= 110:
            robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.0, 0.0, 0.0))
            robot.quadrotor_position.set_relative_yaw(argos_lib.radians(0))
            # Set color of LED to white
            robot.leds.set_all_colors("white")
        elif counter >= 100:
            robot.quadrotor_position.set_relative_position(argos_lib.vector3(-0.5, -0.5, 0.1))
            robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi))
            # Set color of LED to green
            robot.leds.set_all_colors("green")
        elif counter >= 80:
            robot.quadrotor_position.set_relative_position(argos_lib.vector3(0.5, 0.5, 0.1))
            robot.quadrotor_position.set_relative_yaw(argos_lib.radians(math.pi))
        elif counter >= 60:
            robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0, 0.0, 0.2))
            robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0))
        elif counter >= 40:
            robot.quadrotor_position.set_absolute_position(argos_lib.vector3(-1.0, -1.0, 0.5))
            robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(-math.pi))
            # Set color of LED to blue
            robot.leds.set_all_colors("blue")
        elif counter >= 20:
            robot.quadrotor_position.set_absolute_position(argos_lib.vector3(1.0, 1.0, 0.5))
            robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(math.pi))
        elif counter >= 0:
            robot.quadrotor_position.set_absolute_position(argos_lib.vector3(0.0, 0.0, 0.5))
            robot.quadrotor_position.set_absolute_yaw(argos_lib.radians(0))


########################################################
######################## RESET #########################
########################################################

def reset():
    global counter, startFlag
    counter = 0
    startFlag = True
    robot.logprint("reset")


########################################################
####################### DESTROY ########################
########################################################

def destroy():
    robot.logprint("destroy")