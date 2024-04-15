/**
 * @file: py_actusensor_wrapper_crazyflie.cpp
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#include "py_actusensor_wrapper_crazyflie.h"
#include "py_wrapper.h"
#include <boost/python.hpp>

using namespace argos;

/****************************************/
/****************************************/

CVariableWrapper::CVariableWrapper() {}

const std::string CVariableWrapper::GetId() {
  return m_cId;
}

void CVariableWrapper::SetId(const std::string id) {
  m_cId = id;
}

void CVariableWrapper::SetAttribute(const std::string& key, const std::string& value) {
  m_cAttributes[key] = value;
}

const std::string CVariableWrapper::GetAttribute(const std::string& key) {
  return m_cAttributes[key];
}

const std::string CVariableWrapper::GetAllAttributes() {
  std::map<std::string, std::string>::iterator it = m_cAttributes.begin();
  std::string json = "{";

    for (std::pair<std::string, std::string> attr : m_cAttributes) 
    {
        std::string key = attr.first;
        std::string value = attr.second;
        json.append("\"" + key + "\"" + ": " + "\"" + value+ "\"" + ", ");
    }
    if (!json.empty())
        json.pop_back();
        json.pop_back();
    json.append("}");
    return json;
}

/****************************************/
/****************************************/

CCrazyflieSpeedWrapper::CCrazyflieSpeedWrapper() {}

void CCrazyflieSpeedWrapper::SetLinearVelocity(const CVector3& c_velocity) {
    if (m_pcSpdAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Speed Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcSpdAct->SetLinearVelocity(c_velocity);
    
}

void CCrazyflieSpeedWrapper::SetRotationalSpeed(const CRadians& c_speed) {
    if (m_pcSpdAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Speed Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcSpdAct->SetRotationalSpeed(c_speed);
}

/****************************************/
/****************************************/

CCrazyfliePositionSensorWrapper::CCrazyfliePositionSensorWrapper() {}

boost::python::list CCrazyfliePositionSensorWrapper::GetPosition() const {
    if (m_pcPosSens == nullptr) {
        ActusensorsWrapper::Logprint(
            "Positioning Sensor is not implemented or not stated in XML config.");
        return {};
    }
    // Probably there is an better way to convert CVector3 to boost::python::list
    boost::python::list position;
    position.append((float) m_pcPosSens->GetReading().Position[0]);
    position.append((float) m_pcPosSens->GetReading().Position[1]);
    position.append((float) m_pcPosSens->GetReading().Position[2]);

    return position;
}

Real CCrazyfliePositionSensorWrapper::GetOrientation() const {
    if (m_pcPosSens == nullptr) {
        ActusensorsWrapper::Logprint(
            "Positioning Sensor is not implemented or not stated in XML config.");
        return {};
    }
    // Currently only returns rotation along z and ignores other axis
    CRadians cZAngle, cYAngle, cXAngle;
    m_pcPosSens->GetReading().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

    return cZAngle.GetValue();
}

/****************************************/
/****************************************/

CCrazyfliePositionActuatorWrapper::CCrazyfliePositionActuatorWrapper() {}

void CCrazyfliePositionActuatorWrapper::SetAbsolutePosition(const CVector3& c_pos) {
    if (m_pcPosAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Position Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcPosAct->SetAbsolutePosition(c_pos);
}

void CCrazyfliePositionActuatorWrapper::SetRelativePosition(const CVector3& c_pos) {
    if (m_pcPosAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Position Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcPosAct->SetRelativePosition(c_pos);
}

void CCrazyfliePositionActuatorWrapper::SetAbsoluteYaw(const CRadians& c_yaw) {
    if (m_pcPosAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Position Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcPosAct->SetAbsoluteYaw(c_yaw);
}

void CCrazyfliePositionActuatorWrapper::SetRelativeYaw(const CRadians& c_yaw) {
    if (m_pcPosAct == nullptr) {
        ActusensorsWrapper::Logprint(
            "Position Actuator is not implemented or not stated in XML config.");
        return;
    }
    m_pcPosAct->SetRelativeYaw(c_yaw);
}

/****************************************/
/****************************************/

CCrazyflieLedsActuatorWrapper::CCrazyflieLedsActuatorWrapper() {}

void CCrazyflieLedsActuatorWrapper::SetAllColors(const std::string str_color_name) {
    if (m_pcLedAct == nullptr) {
        ActusensorsWrapper::Logprint("Leds Actuator not implemented or not stated in XML config.");
        return;
    }
    m_pcLedAct->SetAllColors(ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}

void CCrazyflieLedsActuatorWrapper::SetSingleColor(const UInt8 un_led_id, const std::string str_color_name) {
    if (m_pcLedAct == nullptr) {
        ActusensorsWrapper::Logprint("Leds Actuator not implemented or not stated in XML config.");
        return;
    }
    m_pcLedAct->SetSingleColor(un_led_id, ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}

/****************************************/
/****************************************/

CCrazyflieBatteryWrapper::CCrazyflieBatteryWrapper() {}

boost::python::list CCrazyflieBatteryWrapper::GetReading() const {
    if (m_pcBattery == nullptr) {
        ActusensorsWrapper::Logprint(
            "Battery Sensor not implemented or not stated in XML config.");
        return {};
    }
    // Probably there is an better way to convert SReadings to boost::python::list
    boost::python::list readings;
    readings.append((Real) m_pcBattery->GetReading().AvailableCharge);
    readings.append((Real) m_pcBattery->GetReading().TimeLeft); 

    return readings;
}

/****************************************/
/****************************************/

CCrazyflieProximityWrapper::CCrazyflieProximityWrapper() {}

boost::python::list CCrazyflieProximityWrapper::GetReadings() const {
    if (m_pcProximity == nullptr) {
        ActusensorsWrapper::Logprint(
            "Proximity Sensor not implemented or not stated in XML config.");
        return {};
    }
    // Return sensor readings as a python list
    boost::python::list readings;
    readings.append((Real) m_pcProximity->GetReadings()[0]);
    readings.append((Real) m_pcProximity->GetReadings()[1]); 
    readings.append((Real) m_pcProximity->GetReadings()[2]);
    readings.append((Real) m_pcProximity->GetReadings()[3]); 
    readings.append((Real) m_pcProximity->GetReadings()[4]); 
    readings.append((Real) m_pcProximity->GetReadings()[5]);
    readings.append((Real) m_pcProximity->GetReadings()[6]); 
    readings.append((Real) m_pcProximity->GetReadings()[7]); 

    return readings;
}

/****************************************/
/****************************************/