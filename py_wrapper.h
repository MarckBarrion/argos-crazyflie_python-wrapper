/**
 * @file: py_wrapper.h
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#ifndef PY_WRAPPER_H
#define PY_WRAPPER_H

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/math/general.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>

#include "py_actusensor_wrapper_generic.h"
#include "py_environment_wrapper.h"
#include "py_actusensor_wrapper_crazyflie.h" 

#include <iostream>
#include <string>

namespace argos {

class EnvironmentWrapper {
  public:
    EnvironmentWrapper();
    ~EnvironmentWrapper(){};

    static void Logprint(const std::string& str_message);
    /****************************************/
    /****************************************/

    // Define a wrapper for the QTOpenGL functions
    CQTOpenGLUserFunctionsWrapper m_cCQTOpenGLUserFunctionsWrapper;

    // Define a wrapper for the variables
    CVariableWrapper m_cVariableWrapper;

    /****************************************/
    /****************************************/

    // Define functions to access the elements the argos::CByteArray class.
    // Original source: https://mail.python.org/pipermail/cplusplus-sig/2003-June/004024.html
    static void CByteArraySetItem(argos::CByteArray& c_vec, const UInt32 un_index,
                                  const UInt8 un_value);

    static UInt8 CByteArrayGetItem(const argos::CByteArray& c_vec, const UInt32 un_index);

    /****************************************/
    /****************************************/

    // Used to convert vectors to python lists.
    // Original source: http://www.boost.org/doc/libs/1_62_0/libs/python/pyste/doc/wrappers.html
    template <class T> static boost::python::list ToPythonList(std::vector<T> c_vec) {
        typename std::vector<T>::iterator iter;
        boost::python::list list;
        for (iter = c_vec.begin(); iter != c_vec.end(); ++iter) {
            list.append(*iter);
        }
        return list;
    }
};

class ActusensorsWrapper {
  public:
    ActusensorsWrapper();
    ~ActusensorsWrapper(){};

    static void Logprint(const std::string& str_message);

    void SetId(const std::string id);

    bool GetConsensus();

    // Sensors
    void CreateSensor(const std::string str_name, CCI_Sensor* pc_sensor,
                      TConfigurationNode& t_node);

    // Actuators
    void CreateActu(const std::string str_name, CCI_Actuator* pc_actu, TConfigurationNode& t_node);

    // Wrapper for the CColor class.
    class CColorWrapper {
      public:
        argos::CColor m_cColor;
        // Create a color by providing its name.
        CColorWrapper(const std::string str_color_name);
        // Create a color by providing its RGB values.
        CColorWrapper(const UInt8 un_red, const UInt8 un_green, const UInt8 un_blue);
        ~CColorWrapper(){};
    };

    /****************************************/
    /****************************************/

    // Define a wrapper for each actuator and sensor

    // Generic actusensors
    CWheelsWrapper m_cWheelsWrapper;
    CDifferentialSteeringSensorWrapper m_cDifferentialSteeringSensor;
    CVariableWrapper m_cVariableWrapper;
    CPositioningSensorWrapper m_cPositioningWrapper;
    COmnidirectionalCameraWrapper m_cOmnidirectionalCameraWrapper;
    CPerspectiveCameraWrapper m_cPerspectiveCameraWrapper;
    CLedsActuatorWrapper m_cLedsWrapper;
    CRangeAndBearingWrapper m_cRangeAndBearingWrapper;

    CQTOpenGLUserFunctionsWrapper m_cCQTOpenGLUserFunctionsWrapper;
    
    /****************************************/
    /****************************************/
    // Crazyflie Actusensors
    CCrazyflieSpeedWrapper m_cCrazyflieSpeedWrapper;
    CCrazyfliePositionSensorWrapper m_cCrazyfliePositionSensorWrapper;
    CCrazyfliePositionActuatorWrapper m_cCrazyfliePositionActuatorWrapper;
    CCrazyflieLedsActuatorWrapper m_cCrazyflieLedsActuatorWrapper;
    CCrazyflieBatteryWrapper m_cCrazyflieBatteryWrapper;
    CCrazyflieProximityWrapper m_cCrazyflieProximityWrapper;
    CCrazyflieRangeAndBearingWrapper m_cCrazyflieRangeAndBearingWrapper;


    /****************************************/
    /****************************************/

    // Define functions to access the elements the argos::CByteArray class.
    // Original source: https://mail.python.org/pipermail/cplusplus-sig/2003-June/004024.html
    static void CByteArraySetItem(argos::CByteArray& c_vec, const UInt32 un_index,
                                  const UInt8 un_value);

    static UInt8 CByteArrayGetItem(const argos::CByteArray& c_vec, const UInt32 un_index);

    /****************************************/
    /****************************************/

    // Used to convert vectors to python lists.
    // Original source: http://www.boost.org/doc/libs/1_62_0/libs/python/pyste/doc/wrappers.html
    template <class T> static boost::python::list ToPythonList(std::vector<T> c_vec) {
        typename std::vector<T>::iterator iter;
        boost::python::list list;
        for (iter = c_vec.begin(); iter != c_vec.end(); ++iter) {
            list.append(*iter);
        }
        return list;
    }
};

} // namespace argos

#endif
