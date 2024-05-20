# ARGoS-Crazyflie Python Wrapper

## About

This repository provides a Python wrapper for the Crazyflie nano-quadcopter from Bitcraze, designed for use with the ARGoS Multi-robot Simulator.

**Author: Marck Herzon C. Barrion (2024)**

To cite, use the paper details:
* Author: Marck Herzon C. Barrion
* Title: [Blockchain-Enabled Consensus in Swarm Robotics: Integration with Crazyflie Drones and ARGoS]
* doi: 

Description:
* This wrapper allows for the control of the Crazyflie simulator model using Python scripts and controllers.
* This project extends the functionalities of the Crazyflie model developed by Stolfi and Danoy (see details below), adding the following features:
    - Multi-ranger Deck (Proximity Sensor)
    - Ground Sensor (IR-based Sensor) 
    - Range and Bearing Sensor and Actuator
    - Entity Distribution - XML

This work is based on the following resources:
* ARGoS-Python Wrapper 
    - Author: Ken Hasselmann
    - Repository: https://github.com/KenN7/argos-python

* ARGoS-Crazyflie Model
    - Authors: Daniel H. Stolfi and Gregoire Danoy
    - Paper: ["An ARGoS plug-in for the Crazyflie drone"](https://arxiv.org/abs/2401.16948)
    - Repository: https://gitlab.uni.lu/adars/crazyflie

* ARGoS Simulator
    - Author: Carlo Pinciroli
    - Paper: ["ARGoS: a Modular, Parallel, Multi-Engine Simulator for Multi-Robot Systems"](https://link.springer.com/article/10.1007/s11721-012-0072-5)
    - Repository: https://github.com/ilpincy/argos3

  
## Pre-requisites
See [ENVSETUP.md](https://github.com/marckbarrion/argos-crazyflie_python/blob/main/ENVSETUP.md#environmental-setup-for-the-crazyflie-swarm-blockchain-project) for a complete guide on system and library requirements and dependencies.

## Instructions

1. To use the code, install the ARGoS-Crazyflie baseline model.

* The extended version is used in this project: 
    - Link: https://github.com/marckbarrion/argos-crazyflie_python-baseline

* To view the original work, use Stolfi and Danoy's project.
    - Link: https://gitlab.uni.lu/adars/crazyflie

2. Once installed, clone this repository
```shell
git clone https://github.com/MarckBarrion/argos-crazyflie_python-wrapper
```

2. Go to the installation root directory

```shell
cd argos-crazyflie_python-wrapper
```

3. Build and compile using CMake

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Running Examples

Run examples using the following codes:

1. Speed Actuator and Positioning Sensor
```shell
argos3 -c examples/1/crazyflie_speed.argos
```

2. Position Actuator and Positioning Sensor
```shell
argos3 -c examples/2/crazyflie_position.argos
```

3. Led Actuator
```shell
argos3 -c examples/3/crazyflie_led.argos
```

4. Battery Level Sensor
```shell
argos3 -c examples/4/crazyflie_battery.argos
```

5. Battery Level Sensor
```shell
argos3 -c examples/5/crazyflie_battery.argos
```

To test all the functionalities in one experiment, run the "crazyflie_general.argos" example.

```shell
argos3 -c examples/crazyflie_general.argos
```
