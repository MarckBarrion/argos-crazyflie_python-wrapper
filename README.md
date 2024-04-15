# ARGoS-Crazyflie Python Wrapper

## About

This repository provides a python wrapper for the Crazyflie nano-quadcopter of Bitcraze for the ARGoS Multi-robot Simulator.

**Author: Marck Herzon C. Barrion (2024)**

Description:
* This wrapper allows control of the crazyflie simulator model using python scripts and controllers.
* This project extends the functionalities of the Crazyflie model of Stolfi and Danoy (see details below) to include the following:
    - Multi-ranger Deck (Proximity Sensor)
    - Ground sensor (IR-based sensor)
    - Range and Bearing Sensor and Actuator

This work is based from the following:
* ARGoS-Python Wrapper 
    - Author: Ken Hasselmann
    - Repository: https://github.com/KenN7/argos-python

* ARGoS-Crazyflie Model
    - Authors: Daniel H. Stolfi and Gregoire Danoy
    - Paper: An ARGoS plug-in for the Crazyflie drone (https://arxiv.org/abs/2401.16948)
    - Repository: https://gitlab.uni.lu/adars/crazyflie

* ARGoS Simulator
    - Author: Carlo Pinciroli
    - Paper: ARGoS: a Modular, Parallel, Multi-Engine Simulator for Multi-Robot Systems (https://link.springer.com/article/10.1007/s11721-012-0072-5)
    - Repository: https://github.com/ilpincy/argos3

To cite this, use the following paper:
    - Author: Marck Herzon C. Barrion
    - Paper: []

## Instructions

1. To use the code, clone the repository
```shell
git clone 
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
sudo make install
```

## Running Examples

Run examples using the following codes:

1. Speed Actuator and Positioning Sensor
```shell
argos3 -c experiments/1/crazyflie_speed.argos
```

2. Position Actuator and Positioning Sensor
```shell
argos3 -c experiments/2/crazyflie_position.argos
```

3. Led Actuator
```shell
argos3 -c experiments/3/crazyflie_led.argos
```

4. Battery Level Sensor
```shell
argos3 -c experiments/4/crazyflie_battery.argos
```

5. Battery Level Sensor
```shell
argos3 -c experiments/5/crazyflie_battery.argos
```

To test all the functionalities in one experiment, run the "crazyflie_general.argos" example.

```shell
argos3 -c experiments/crazyflie_general.argos
```
