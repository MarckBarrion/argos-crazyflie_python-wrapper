/**
 * @file: py_wrapper.cpp
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#include "py_wrapper.h"
#include <argos3/core/utility/math/vector3.h>

using namespace argos;
using namespace boost::python;

/****************************************/
/****************************************/

EnvironmentWrapper::EnvironmentWrapper() {}

void EnvironmentWrapper::Logprint(const std::string& str_message) {
    std::cout << str_message << std::endl;
}



/****************************************/
/****************************************/

ActusensorsWrapper::ActusensorsWrapper() {}

void ActusensorsWrapper::SetId(const std::string id) {
    m_cVariableWrapper.m_cId = id;
}

void ActusensorsWrapper::Logprint(const std::string& str_message) {
    std::cout << str_message << std::endl;
}


/****************************************/
/****************************************/

// Initialize the actuator specified by the provided name.

// NOTE: the Init function gives problems for all the sensors/actuators that use the "media"
// parameter. When the argos file is loaded, the following error is given:
//    [FATAL] Error parsing attribute "medium"
//    Attribute does not exist <ticpp.h@1791>
// The sensors/actuators seem to work even without it, so for now it has been disabled.
void ActusensorsWrapper::CreateActu(const std::string str_name, CCI_Actuator* pc_actu,
                                    TConfigurationNode& t_node) {
    if (str_name == "differential_steering") {
        m_cWheelsWrapper.m_pcWheels = dynamic_cast<CCI_DifferentialSteeringActuator*>(pc_actu);
        m_cWheelsWrapper.m_pcWheels->Init(t_node);
    } else if (str_name == "generic_leds") {
        m_cLedsWrapper.m_pcLeds = (CCI_LEDsActuator*)pc_actu;
        // m_cLedsWrapper.m_pcLeds->Init(t_node);
    } else if (str_name == "generic_range_and_bearing") {
        m_cRangeAndBearingWrapper.m_pcRABA = (CCI_RangeAndBearingActuator*)pc_actu;
        // m_cRangeAndBearingWrapper.m_pcRABA->Init(t_node);
    }

    /****************************************/
    /****************************************/
    // Crazyflie speed actuator
    else if (str_name == "quadrotor_speed") {
        m_cCrazyflieSpeedWrapper.m_pcSpdAct = dynamic_cast<CCI_QuadRotorSpeedActuator*>(pc_actu);
        m_cCrazyflieSpeedWrapper.m_pcSpdAct->Init(t_node);
    }
    // Crazyflie position actuator
    else if (str_name == "quadrotor_position") {
        m_cCrazyfliePositionActuatorWrapper.m_pcPosAct = dynamic_cast<CCI_QuadRotorPositionActuator*>(pc_actu);
        m_cCrazyfliePositionActuatorWrapper.m_pcPosAct->Init(t_node);
    }
    // Crazyflie leds actuator
    else if (str_name == "leds") {
        m_cCrazyflieLedsActuatorWrapper.m_pcLedAct = (CCI_LEDsActuator*)pc_actu;
    }
    // Crazyflie range and bearing actuator
    else if (str_name == "range_and_bearing") {
        m_cCrazyflieRangeAndBearingWrapper.m_pcRABA = (CCI_RangeAndBearingActuator*)pc_actu;
    }
    /****************************************/
    /****************************************/
}

/****************************************/
/****************************************/

// Initialize the sensor specified by the provided name.
void ActusensorsWrapper::CreateSensor(const std::string str_name, CCI_Sensor* pc_sensor,
                                      TConfigurationNode& t_node) {

    // Generic sensors.
    if (str_name == "colored_blob_omnidirectional_camera") {
        m_cOmnidirectionalCameraWrapper.m_pcOmniCam = (CCI_ColoredBlobOmnidirectionalCameraSensor*)pc_sensor;
        // m_cOmnidirectionalCameraWrapper.m_pcOmniCam->Init(t_node);

    } else if (str_name == "colored_blob_perspective_camera") {
        m_cPerspectiveCameraWrapper.m_pcPerspCam = (CCI_ColoredBlobPerspectiveCameraSensor*)pc_sensor;
        // m_cPerspectiveCameraWrapper.m_pcPerspCam->Init(t_node);

    } else if (str_name == "generic_range_and_bearing") {
        m_cRangeAndBearingWrapper.m_pcRABS = (CCI_RangeAndBearingSensor*)pc_sensor;    
        // m_cRangeAndBearingWrapper.m_pcRABS->Init(t_node);

    } else if (str_name == "differential_steering") {
        m_cDifferentialSteeringSensor.m_pcDifferentialSteeringSensor = (CCI_DifferentialSteeringSensor*)pc_sensor;
    } else if (str_name == "generic_positioning") {
        m_cPositioningWrapper.m_pcPositioning = (CCI_PositioningSensor*)pc_sensor;
    } 

    /****************************************/
    /****************************************/
    /****************************************/
    // Crazyflie position sensor
    else if (str_name == "positioning") {
        m_cCrazyfliePositionSensorWrapper.m_pcPosSens = dynamic_cast<CCI_PositioningSensor*>(pc_sensor);
        m_cCrazyfliePositionSensorWrapper.m_pcPosSens->Init(t_node);
    }
    // Crazyflie battery sensor
    else if (str_name == "crazyflie_battery") {
        m_cCrazyflieBatteryWrapper.m_pcBattery = (CCI_BatterySensor*)pc_sensor;
    }
    // Crazyflie proximity sensor
    else if (str_name == "crazyflie_proximity") {
        m_cCrazyflieProximityWrapper.m_pcProximity = (CCI_ProximitySensor*)pc_sensor;
    }
    // Crazyflie range and bearing sensor
    else if (str_name == "range_and_bearing") {
        m_cCrazyflieRangeAndBearingWrapper.m_pcRABS = (CCI_RangeAndBearingSensor*)pc_sensor;    

    }
    // Crazyflie ground sensor
    else if (str_name == "crazyflie_ground") {
        m_cCrazyflieGroundWrapper.m_pcGroundSensor = dynamic_cast<CCI_GroundSensor*>(pc_sensor);
    } 

}

/****************************************/
/****************************************/

// Create a color by providing its name.
ActusensorsWrapper::CColorWrapper::CColorWrapper(const std::string str_color_name) {
    if (str_color_name == "red")
        m_cColor = argos::CColor::RED;
    else if (str_color_name == "black")
        m_cColor = argos::CColor::BLACK;
    else if (str_color_name == "blue")
        m_cColor = argos::CColor::BLUE;
    else if (str_color_name == "green")
        m_cColor = argos::CColor::GREEN;
    else if (str_color_name == "yellow")
        m_cColor = argos::CColor::YELLOW;
    else if (str_color_name == "white")
        m_cColor = argos::CColor::WHITE;
    else if (str_color_name == "gray10")
        m_cColor = argos::CColor::GRAY10;
    else if (str_color_name == "gray20")
        m_cColor = argos::CColor::GRAY20;
    else if (str_color_name == "gray30")
        m_cColor = argos::CColor::GRAY30;
    else if (str_color_name == "gray40")
        m_cColor = argos::CColor::GRAY40;
    else if (str_color_name == "gray50")
        m_cColor = argos::CColor::GRAY50;
    else if (str_color_name == "gray60")
        m_cColor = argos::CColor::GRAY60;
    else if (str_color_name == "gray70")
        m_cColor = argos::CColor::GRAY70;
    else if (str_color_name == "gray80")
        m_cColor = argos::CColor::GRAY80;
    else if (str_color_name == "gray90")
        m_cColor = argos::CColor::GRAY90;
    else if (str_color_name == "magenta")
        m_cColor = argos::CColor::MAGENTA;
    else if (str_color_name == "cyan")
        m_cColor = argos::CColor::CYAN;
    else if (str_color_name == "orange")
        m_cColor = argos::CColor::ORANGE;
    else if (str_color_name == "brown")
        m_cColor = argos::CColor::BROWN;
    else if (str_color_name == "purple")
        m_cColor = argos::CColor::PURPLE;
    else if (str_color_name == "custom")
        m_cColor = argos::CColor(70,160,70,0);
    else if (str_color_name == "custom2")
        m_cColor = argos::CColor(160,110,110,0);
    else
        m_cColor = argos::CColor::WHITE;
}

// Create a color by providing its RGB values.
ActusensorsWrapper::CColorWrapper::CColorWrapper(const UInt8 un_red, const UInt8 un_green,
                                                 const UInt8 un_blue) {
    m_cColor = argos::CColor((const UInt8)un_red, (const UInt8)un_green, (const UInt8)un_blue, 0);
}

/****************************************/
/****************************************/

void ActusensorsWrapper::CByteArraySetItem(argos::CByteArray& c_vec, const UInt32 un_index,
                                           const UInt8 un_value) {
    if (un_index >= 0 && un_index < c_vec.Size()) {
        c_vec[un_index] = un_value;
    } else {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        boost::python::throw_error_already_set();
    }
}

UInt8 ActusensorsWrapper::CByteArrayGetItem(const argos::CByteArray& c_vec, const UInt32 un_index) {
    if (un_index >= 0 && un_index < c_vec.Size()) {
        return c_vec[un_index];
    }
    PyErr_SetString(PyExc_IndexError, "index out of range");
    boost::python::throw_error_already_set();
    return {};
}

/****************************************/
/****************************************/

// BOOST_PYTHON_MODULE(libpy_qtuser_function_interface) {


// }

BOOST_PYTHON_MODULE(libpy_controller_interface) {

    // Export the main "environment" class with the draw functions and variables
     class_<EnvironmentWrapper, boost::shared_ptr<EnvironmentWrapper>, boost::noncopyable>("environment", no_init)
        .def("logprint", &EnvironmentWrapper::Logprint)
        .staticmethod("logprint")
        .add_property("qt_draw", &EnvironmentWrapper::m_cCQTOpenGLUserFunctionsWrapper)
        .add_property("variables", &EnvironmentWrapper::m_cVariableWrapper);

    // Export the main "robot" class with the sensors, actuators and variables
    class_<ActusensorsWrapper, boost::shared_ptr<ActusensorsWrapper>, boost::noncopyable>("robot", no_init)
        .def("logprint", &ActusensorsWrapper::Logprint)
        .staticmethod("logprint")
        .add_property("variables", &ActusensorsWrapper::m_cVariableWrapper)
        .add_property("wheels", &ActusensorsWrapper::m_cWheelsWrapper)
        .add_property("differential_steering", &ActusensorsWrapper::m_cDifferentialSteeringSensor)
        .add_property("colored_blob_omnidirectional_camera", &ActusensorsWrapper::m_cOmnidirectionalCameraWrapper)
        .add_property("colored_blob_perspective_camera", &ActusensorsWrapper::m_cPerspectiveCameraWrapper)
        .add_property("old_position", &ActusensorsWrapper::m_cPositioningWrapper)
        .add_property("old_leds", &ActusensorsWrapper::m_cLedsWrapper)
        .add_property("range_and_bearing", &ActusensorsWrapper::m_cRangeAndBearingWrapper)
        .add_property("quadrotor_speed", &ActusensorsWrapper::m_cCrazyflieSpeedWrapper)
        .add_property("position", &ActusensorsWrapper::m_cCrazyfliePositionSensorWrapper)
        .add_property("quadrotor_position", &ActusensorsWrapper::m_cCrazyfliePositionActuatorWrapper)
        .add_property("leds", &ActusensorsWrapper::m_cCrazyflieLedsActuatorWrapper)
        .add_property("crazyflie_battery", &ActusensorsWrapper::m_cCrazyflieBatteryWrapper)
        .add_property("crazyflie_proximity", &ActusensorsWrapper::m_cCrazyflieProximityWrapper)
        .add_property("range_and_bearing", &ActusensorsWrapper::m_cCrazyflieRangeAndBearingWrapper)
        .add_property("crazyflie_ground", &ActusensorsWrapper::m_cCrazyflieGroundWrapper);

    // Export "QTOpenGLUserFunctionsWrapper" that contains qtuser draw functions
    class_<CQTOpenGLUserFunctionsWrapper, boost::noncopyable>("qtuser_wrapper", no_init)
        .def("set_draw_list", &CQTOpenGLUserFunctionsWrapper::SetDrawList)
        .def("get_draw_list", &CQTOpenGLUserFunctionsWrapper::GetDrawList)  
        .def("circle", &CQTOpenGLUserFunctionsWrapper::DrawCircle)
        .def("ray", &CQTOpenGLUserFunctionsWrapper::DrawRay)
        .def("polygon", &CQTOpenGLUserFunctionsWrapper::DrawPolygon)
        .def("cylinder", &CQTOpenGLUserFunctionsWrapper::DrawCylinder)
        .def("box", &CQTOpenGLUserFunctionsWrapper::DrawBox)
        .def("text", &CQTOpenGLUserFunctionsWrapper::DrawText)
        .def("close_window", &CQTOpenGLUserFunctionsWrapper::CloseWindow);

    // Export "VariableWrapper" that contains a robot's variables
    class_<CVariableWrapper, boost::noncopyable>("variable_wrapper", no_init)
        .def("get_id", &CVariableWrapper::GetId)
        .def("set_attribute", &CVariableWrapper::SetAttribute)
        .def("get_attribute", &CVariableWrapper::GetAttribute)  
        .def("get_all_attributes", &CVariableWrapper::GetAllAttributes);
        
    // Export "WheelsWrapper", wrapper of CCI_DifferentialSteeringActuator.
    class_<CWheelsWrapper, boost::noncopyable>("wheels_wrapper", no_init)
        .def("set_speed", &CWheelsWrapper::SetSpeed);

    // Export "DifferentialSteeringSensorWrapper", wrapper of CCI_DifferentialSteeringSensor.
    class_<CDifferentialSteeringSensorWrapper, boost::noncopyable>("differential_steering_sensor_wrapper", no_init)
        .def("get_readings", &CDifferentialSteeringSensorWrapper::GetReading)
        .def("get_distances", &CDifferentialSteeringSensorWrapper::GetDistances);
 

    // Export "OmnidirectionalCameraWrapper" , wrapper of
    // CCI_ColoredBlobOmnidirectionalCameraSensor.
    class_<COmnidirectionalCameraWrapper, boost::noncopyable>("omnidirectional_camera_wrapper",
                                                              no_init)
        .def("enable", &COmnidirectionalCameraWrapper::Enable)
        .def("disable", &COmnidirectionalCameraWrapper::Disable)
        .def("get_readings", &COmnidirectionalCameraWrapper::GetReadings)
        .def("set_fov", &COmnidirectionalCameraWrapper::setFOV)
        .def("get_counter", &COmnidirectionalCameraWrapper::GetCounter);

    class_<CPerspectiveCameraWrapper, boost::noncopyable>("perspective_camera_wrapper",
                                                              no_init)
        .def("enable", &CPerspectiveCameraWrapper::Enable)
        .def("disable", &CPerspectiveCameraWrapper::Disable)
        .def("get_readings", &CPerspectiveCameraWrapper::GetReadings);

    // Export "PositionSensorWrapper", wrapper of CCI_PositionSensor.
    class_<CPositioningSensorWrapper, boost::noncopyable>("positioning_wrapper",
                                                               no_init)
        .def("get_position", &CPositioningSensorWrapper::GetPosition)
        .def("get_orientation", &CPositioningSensorWrapper::GetOrientation);

    // Export "LedsActuatorWrapper", wrapper of CCI_LEDsActuator.
    class_<CLedsActuatorWrapper, boost::noncopyable>("leds_actuator_wrapper", no_init)
        .def("set_single_color", &CLedsActuatorWrapper::SetSingleColorString)
        .def("set_single_color", &CLedsActuatorWrapper::SetSingleColorRGB)
        .def("set_all_colors", &CLedsActuatorWrapper::SetAllColorsString)
        .def("set_all_colors", &CLedsActuatorWrapper::SetAllColorsRGB);

    // Export RangeAndBearingWrapper, wrapper of CCI_RangeAndBearingActuator and
    // CCI_RangeAndBearingSensor.
    class_<CRangeAndBearingWrapper, boost::noncopyable>("m_cRangeAndBearingWrapper", no_init)
        .def("clear_data", &CRangeAndBearingWrapper::ClearData)
        .def("set_data", &CRangeAndBearingWrapper::SetData)
        .def("get_readings", &CRangeAndBearingWrapper::GetReadings);

    // Export a CRadians - float map, used for the readings of the Distance Scanner Sensor.
    // The map can be iterated. For a given map entry, get the key with map_entry.key()
    // (map_entry.key().value() to get the actual angle value),
    // and the value with map_entry.data()
    class_<std::map<argos::CRadians, Real>>("distance_sensor_readings_map")
        .def(boost::python::map_indexing_suite<std::map<argos::CRadians, Real>>());

    // Export the CRadians class, used by the readings of various sensors.
    // TODO: add more properties
    class_<argos::CRadians>("radians", init<>())
        .def(init<Real>())
        .def("value", &argos::CRadians::GetValue);

    // Export the SBlob class, used to store the readings of the omnidirectional camera.
    class_<argos::CCI_ColoredBlobOmnidirectionalCameraSensor::SBlob>(
        "omnidirectional_camera_packet", no_init)
        .def_readonly("distance",
                      &argos::CCI_ColoredBlobOmnidirectionalCameraSensor::SBlob::Distance)
        .def_readonly("angle", &argos::CCI_ColoredBlobOmnidirectionalCameraSensor::SBlob::Angle)
        .def_readonly("color", &argos::CCI_ColoredBlobOmnidirectionalCameraSensor::SBlob::Color);

    // Export the SPacket class, used to store the readings of the range and bearing sensor.
    class_<argos::CCI_RangeAndBearingSensor::SPacket>("range_and_bearing_packet", no_init)
        .add_property("range", &argos::CCI_RangeAndBearingSensor::SPacket::Range)
        .add_property("horizontal_bearing",
                      &argos::CCI_RangeAndBearingSensor::SPacket::HorizontalBearing)
        .add_property("vertical_bearing",
                      &argos::CCI_RangeAndBearingSensor::SPacket::VerticalBearing)
        .add_property("data", &argos::CCI_RangeAndBearingSensor::SPacket::Data);

    class_<argos::CVector2>("vector2", init<>())
        .def(init<Real, Real>())
        .add_property("x", &argos::CVector2::GetX, &argos::CVector2::SetX)
        .add_property("y", &argos::CVector2::GetY, &argos::CVector2::SetY)
        .def_readonly("length", &argos::CVector2::Length)
        .def_readonly("angle", &argos::CVector2::Angle)
        .def_readonly("square_length", &argos::CVector2::SquareLength);

    // Export the ColorWrapper class.
    class_<ActusensorsWrapper::CColorWrapper>("color", init<std::string>())
        .def(init<UInt8, UInt8, UInt8>())
        .add_property("raw_color", &ActusensorsWrapper::CColorWrapper::m_cColor);
    // TODO: add other color stuff

    // Export the CColor class. This class is not directly usable in python,
    // but it is exported to simplify the usage of colors in python.
    class_<argos::CColor>("raw_color", no_init).def("__eq__", &argos::CColor::operator==);

    // Export the CByteArray class, and define new functions on it to access its data.
    class_<argos::CByteArray>("c_byte_array", no_init)
        .def("__getitem__", &ActusensorsWrapper::CByteArrayGetItem)
        .def("__setitem__", &ActusensorsWrapper::CByteArraySetItem);


    /****************************************/
    /****************************************/
    /****************************************/
    /****************************************/

    // Export "CrazyflieSpeedWrapper", wrapper of Crazyflie Speed Actuator 
    class_<CCrazyflieSpeedWrapper, boost::noncopyable>("quadrotor_speed_wrapper", no_init)
        .def("set_linear_velocity", &CCrazyflieSpeedWrapper::SetLinearVelocity)
        .def("set_rotational_velocity", &CCrazyflieSpeedWrapper::SetRotationalSpeed);

    /****************************************/
    /****************************************/

    // Export "CrazyfliePositionActuatorWrapper", wrapper of Crazyflie Position Actuator 
    class_<CCrazyfliePositionActuatorWrapper, boost::noncopyable>("quadrotor_position_wrapper", no_init)
        .def("set_absolute_position", &CCrazyfliePositionActuatorWrapper::SetAbsolutePosition)
        .def("set_relative_position", &CCrazyfliePositionActuatorWrapper::SetRelativePosition)
        .def("set_absolute_yaw", &CCrazyfliePositionActuatorWrapper::SetAbsoluteYaw)
        .def("set_relative_yaw", &CCrazyfliePositionActuatorWrapper::SetRelativeYaw);

    /****************************************/
    /****************************************/

    // Export "CrazyfliePositionSensorWrapper" wrapper of CCI_PositioningSensor
    class_<CCrazyfliePositionSensorWrapper, boost::noncopyable>("crazyflie_positioning_wrapper",
                                                               no_init)
        .def("get_position", &CCrazyfliePositionSensorWrapper::GetPosition)
        .def("get_orientation", &CCrazyfliePositionSensorWrapper::GetOrientation);

    /****************************************/
    /****************************************/
    // Export "LedsActuatorWrapper", wrapper of CCI_LEDsActuator.
    class_<CCrazyflieLedsActuatorWrapper, boost::noncopyable>("crazyflie_leds_actuator_wrapper", no_init)
        .def("set_all_colors", &CCrazyflieLedsActuatorWrapper::SetAllColors)
        .def("set_single_color", &CCrazyflieLedsActuatorWrapper::SetSingleColor);

    /****************************************/
    /****************************************/

    // Export "CrazyflieBatteryWrapper", wrapper of CCI_BatterySensor.
    class_<CCrazyflieBatteryWrapper, boost::noncopyable>("crazyflie_battery_sensor_wrapper", no_init)
        .def("get_reading", &CCrazyflieBatteryWrapper::GetReading);

    /****************************************/
    /****************************************/

    // Export "CrazyflieProximityWrapper", wrapper of CCI_ProximitySensor.
    class_<CCrazyflieProximityWrapper, boost::noncopyable>("crazyflie_proximity_sensor_wrapper", no_init)
        .def("get_readings", &CCrazyflieProximityWrapper::GetReadings);

    /****************************************/
    /****************************************/

    // Export RangeAndBearingWrapper, wrapper of CCI_RangeAndBearingActuator and
    // CCI_RangeAndBearingSensor.
    class_<CCrazyflieRangeAndBearingWrapper, boost::noncopyable>("m_cCrazyflieRangeAndBearingWrapper", no_init)
        .def("clear_data", &CCrazyflieRangeAndBearingWrapper::ClearData)
        .def("set_data", &CCrazyflieRangeAndBearingWrapper::SetData)
        .def("get_readings", &CCrazyflieRangeAndBearingWrapper::GetReadings);
    /****************************************/
    /****************************************/

    // Export "CrazyflieGroundWrapper", wrapper of CCI_GroundSensor.
    class_<CCrazyflieGroundWrapper, boost::noncopyable>("crazyflie_ground_sensor_wrapper", no_init)
        .def("get_readings", &CCrazyflieGroundWrapper::GetReadings);

    /****************************************/
    /****************************************/
    
    // Export the CVector3 class
    class_<argos::CVector3>("vector3", init<>())
        .def(init<Real, Real, Real>())  // Constructor with X, Y, Z values
        .add_property("x", &argos::CVector3::GetX, &argos::CVector3::SetX)  // Expose X component
        .add_property("y", &argos::CVector3::GetY, &argos::CVector3::SetY)  // Expose Y component
        .add_property("z", &argos::CVector3::GetZ, &argos::CVector3::SetZ)  // Expose Z component
        .def_readonly("length", &argos::CVector3::Length)
        .def_readonly("square_length", &argos::CVector3::SquareLength);

    /****************************************/
    /****************************************/
}