/**
 * @file: py_actusensor_wrapper_crazyflie.h
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#ifndef PY_ACTUSENSOR_WRAPPER_CRAZYFLIE_H
#define PY_ACTUSENSOR_WRAPPER_CRAZYFLIE_H

// Including necessary libraries and dependencies for interfacing with Python, handling data structures, and interfacing with ARGoS
#include <boost/python.hpp>
#include <boost/variant.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <argos3/core/utility/logging/argos_log.h>
#include <iostream>
#include <string>
#include <map>

// ARGoS-related includes for control interfaces, utilities, and entities
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/general.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/physics_engine/physics_model.h>
#include <argos3/core/control_interface/ci_sensor.h>

// Plugin-specific includes for robot and sensor interfaces in ARGoS
#include <argos3/plugins/robots/generic/control_interface/ci_battery_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_colored_blob_perspective_camera_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_speed_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_proximity_sensor.h>
#include <argos3/plugins/simulator/physics_engines/pointmass3d/pointmass3d_model.h>
#include <argos3/plugins/simulator/entities/quadrotor_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>

namespace argos { 

/****************************************/
/****************************************/

// Wrapper for getting the values of a robot's variables
class CVariableWrapper {
    public:
        CVariableWrapper();
        ~CVariableWrapper(){};

    void SetId(const std::string id);
    const std::string GetId();
    std::string m_cId;

    void SetAttribute(const std::string& key, const std::string& value);
    const std::string GetAttribute(const std::string& key);
    const std::string GetAllAttributes();
    std::map<std::string, std::string> m_cAttributes;

};

/****************************************/
/****************************************/

// Wrapper for Crazyflie Speed Actuator
class CCrazyflieSpeedWrapper {
public:
    CCrazyflieSpeedWrapper();
    ~CCrazyflieSpeedWrapper() {};

    argos::CCI_QuadRotorSpeedActuator* m_pcSpdAct;

    void SetLinearVelocity(const CVector3& c_velocity);
    void SetRotationalSpeed(const CRadians& c_speed);

};

/****************************************/
/****************************************/

// Wrapper for Crazyflie Positioning Sensor
class CCrazyfliePositionSensorWrapper {
public:
    CCrazyfliePositionSensorWrapper();
    ~CCrazyfliePositionSensorWrapper(){};

    argos::CCI_PositioningSensor* m_pcPosSens;

    boost::python::list GetPosition() const;
    Real GetOrientation() const;
};

/****************************************/
/****************************************/

// Wrapper for Crazyflie Position Actuator
class CCrazyfliePositionActuatorWrapper {
public:
    CCrazyfliePositionActuatorWrapper();
    ~CCrazyfliePositionActuatorWrapper() {};

    argos::CCI_QuadRotorPositionActuator* m_pcPosAct;

    void SetAbsolutePosition(const CVector3& c_pos);
    void SetRelativePosition(const CVector3& c_pos);
    void SetAbsoluteYaw(const CRadians& c_yaw);
    void SetRelativeYaw(const CRadians& c_yaw);

};

/****************************************/
/****************************************/

// Wrapper for Crazyflie LED Actuator
class CCrazyflieLedsActuatorWrapper {
public:
    CCrazyflieLedsActuatorWrapper();
    ~CCrazyflieLedsActuatorWrapper() {};

    argos::CCI_LEDsActuator* m_pcLedAct;

    // Set the color of every led, given its name.
    void SetAllColors(const std::string str_color_name);

    // Set the color of a given led, given its name.
    void SetSingleColor(const UInt8 un_led_id, const std::string str_color_name);
};

/****************************************/
/****************************************/

// Wrapper for Crazyflie Battery Sensor
class CCrazyflieBatteryWrapper {
public:
    CCrazyflieBatteryWrapper();
    ~CCrazyflieBatteryWrapper(){};

    argos::CCI_BatterySensor* m_pcBattery;

    boost::python::list GetReading() const;
};

/****************************************/
/****************************************/

// Wrapper for Crazyflie Proximity Sensor
class CCrazyflieProximityWrapper {
public:
    CCrazyflieProximityWrapper();
    ~CCrazyflieProximityWrapper(){};

    argos::CCI_ProximitySensor* m_pcProximity;

    boost::python::list GetReadings() const;
};

/****************************************/
/****************************************/

} //namespace argos

#endif