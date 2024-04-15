/**
 * @file: py_loop_function.cpp
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#include "py_loop_function.h"

using namespace argos;
using namespace boost::python;

#define INIT_MODULE_LOOP_FUNCTION PyInit_libpy_loop_function_interface
extern "C" PyObject* INIT_MODULE_LOOP_FUNCTION();

// TODO: I had to add these lines and the line PyImport_AppendInittab("libpy_controller_interface", INIT_MODULE_CONTROLLER)
// in this file, otherwise I god an error that libpy_controller_interface is not a built-in module
#define INIT_MODULE_CONTROLLER PyInit_libpy_controller_interface
extern "C" PyObject* INIT_MODULE_CONTROLLER();

// TODO: I had to add these lines and the line PyImport_AppendInittab("libpy_qtuser_function_interface", INIT_MODULE_QTUSER_FUNCTION)
// in this file, otherwise I god an error that libpy_qtuser_function_interface is not a built-in module
#define INIT_MODULE_QTUSER_FUNCTION PyInit_libpy_qtuser_function_interface
extern "C" PyObject* INIT_MODULE_QTUSER_FUNCTION();

BOOST_PYTHON_MODULE(libpy_loop_function_interface) {

}

CPyLoopFunction::CPyLoopFunction() {
  // init python

  // TODO: Remove from loop function and only call in controller
  // PyImport_AppendInittab("libpy_qtuser_function_interface", INIT_MODULE_QTUSER_FUNCTION); 
  PyImport_AppendInittab("libpy_controller_interface", INIT_MODULE_CONTROLLER); 
  // TODO: Remove from loop function and only call in controller

  PyImport_AppendInittab("libpy_loop_function_interface", INIT_MODULE_LOOP_FUNCTION);
  if (!Py_IsInitialized()) {
    Py_Initialize();
  }
  m_loop_interpreter = Py_NewInterpreter();
    // init main module and namespace
  m_loop_main = import("__main__");
  m_loop_namesp = m_loop_main.attr("__dict__");
}


void CPyLoopFunction::Init(TConfigurationNode& t_node) {

  TConfigurationNode& tParams = GetNode(t_node, "params");
  
  /* Load script */
  std::string strScriptFileName;
  GetNodeAttributeOrDefault(tParams, "script", strScriptFileName, strScriptFileName);
  if (strScriptFileName == "") {
    THROW_ARGOSEXCEPTION("Loop function: Error loading python script \"" << strScriptFileName << "\""
      << std::endl);
  }
  // exec user script
  try {
    m_loop_script = exec_file(strScriptFileName.c_str(), m_loop_namesp, m_loop_namesp);

    std::cout << "Loop function: strScript:" << strScriptFileName << std::endl;
  } catch (error_already_set) {
    PyErr_Print();
  }


  // Iterate over all robots and add them to a boost list
  boost::python::list allRobots;    

  // Crazyflie
  CSpace::TMapPerType& m_cCrazyflie = GetSpace().GetEntitiesByType("crazyflie");
  for(CSpace::TMapPerType::iterator it = m_cCrazyflie.begin(); it != m_cCrazyflie.end(); ++it)
  {
    /* Get handle to crazyflie entity and controller */
    CCrazyflieEntity& cCrazyflie = *any_cast<CCrazyflieEntity*>(it->second);

    CPyController& cController =  dynamic_cast<CPyController&>(cCrazyflie.GetControllableEntity().GetController());

    allRobots.append(cController.getActusensors());
  }
  m_loop_namesp["allrobots"]  = allRobots;

/****************************************/
/****************************************/

  // To-do: find way to access environment handle to access CPyQTUserFunction from loop function
  /* Get handle to environment */
  // cEnvironment = dynamic_cast<CPyQTUserFunction&>();
  // m_environment = cEnvironment.getEnvironment();
  // m_loop_namesp["environment"]  = m_environment;
  
  try {
    // Import the wrapper's lib
    PyRun_SimpleString("import libpy_loop_function_interface as lib");
    object lib = import("libpy_loop_function_interface");
    

    // Launch Python init function
    object init_f = m_loop_main.attr("init");
    init_f();
  } catch (error_already_set) {
    PyErr_Print();
  }

}

void CPyLoopFunction::Reset() {
  // launch python reset function
  try {
    object reset_f = m_loop_main.attr("reset");
    reset_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::Destroy() {
  
  // Launch Python destroy function
  try {
    object destroy_f = m_loop_main.attr("destroy");
    destroy_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::PreStep() {

  // Launch Python pre_step function
  try {
    object pre_step_f = m_loop_main.attr("pre_step");
    pre_step_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::PostStep() {
  // Launch Python post_step function
  try {
    object post_step_f = m_loop_main.attr("post_step");
    post_step_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

bool CPyLoopFunction::IsExperimentFinished() {

// Launch Python is_experiment_finished function
  try {
    object is_experiment_finished_f = m_loop_main.attr("is_experiment_finished");
    return is_experiment_finished_f();
  } catch (error_already_set) {
    PyErr_Print();
    return true;
  }
}

CColor CPyLoopFunction::GetFloorColor() {

// Launch Python is_experiment_finished function
  try {
    object get_floor_color_f = m_loop_main.attr("get_floor_color");

    std::cout << "Testing GetFloorColor" << std::endl;
    return CColor::WHITE;
  } catch (error_already_set) {
    PyErr_Print();
    return CColor::WHITE;
  }
}

void CPyLoopFunction::PostExperiment() {
  // Launch Python post_experiment function
  try {
    object post_experiment_f = m_loop_main.attr("post_experiment");
    post_experiment_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

REGISTER_LOOP_FUNCTIONS(CPyLoopFunction, "py_loop_function")
