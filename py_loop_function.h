/**
 * @file: py_loop_function.h
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#ifndef PY_LOOP_FUNCTION_H
#define PY_LOOP_FUNCTION_H

#include <boost/make_shared.hpp>
#include <boost/python.hpp>

#include <py_controller.h>
#include <py_qtuser_function.h>

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/simulator/entities/quadrotor_entity.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>


using namespace argos;

class CPyLoopFunction : public CLoopFunctions {

 public:
  CPyLoopFunction();
  virtual ~CPyLoopFunction(){};
  
  virtual void Init(TConfigurationNode& t_node);

  virtual void Reset();

  virtual void Destroy ();

  virtual void PreStep();

  virtual void PostStep();

  virtual bool IsExperimentFinished();

  virtual CColor GetFloorColor();

  virtual void PostExperiment();

 private:
  
    boost::python::object m_loop_main;
    boost::python::object m_loop_namesp;
    boost::python::object m_loop_script;
    PyThreadState* m_loop_interpreter;
    boost::shared_ptr<EnvironmentWrapper> m_environment;
};

#endif
