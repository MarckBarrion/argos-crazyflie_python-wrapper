/**
 * @file: py_qtuser_function.h
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#ifndef PY_QTUSER_FUNCTION_H
#define PY_QTUSER_FUNCTION_H

#include <boost/make_shared.hpp>
#include <boost/python.hpp>

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>

#include <py_controller.h>
#include "py_wrapper.h"

namespace argos { 

class CPyQTUserFunction : public CQTOpenGLUserFunctions {

 public:

   CPyQTUserFunction();

   virtual ~CPyQTUserFunction () {}

   virtual void Init(TConfigurationNode& t_node);
   void DrawInWorld();
   void Destroy();

   // Crazyflie 
   void Draw(CCrazyflieEntity& c_entity);

   virtual boost::shared_ptr<EnvironmentWrapper> getEnvironment();

 private:
  
    boost::python::object m_qtuser_main;
    boost::python::object m_qtuser_namesp;
    boost::python::object m_qtuser_script;
    PyThreadState* m_qtuser_interpreter;
    boost::shared_ptr<EnvironmentWrapper> m_environment;

  };

}

#endif